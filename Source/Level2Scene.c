//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.c
// Author(s):	Xanna Fuller (xan.fuller)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "DGL.h"
#include "Stream.h"
#include "Scene.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Transform.h"
#include "Physics.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Vector2D.h"

#include "SceneSystem.h"
#include "DemoScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const float spaceshipSpeed = 500.f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	Mesh* mesh;
	Entity* spaceship;

} Level2Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level2SceneLoad(void);
static void Level2SceneInit(void);
static void Level2SceneUpdate(float dt);
static void Level2SceneExit(void);
static void Level2SceneUnload(void);
static void Level2SceneRender(void);
static void Level2SceneMovementController(Entity* entity);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level2Scene instance =
{
	// Initialize the base structure:
	{ "Level2", Level2SceneLoad, Level2SceneInit, Level2SceneUpdate, Level2SceneRender, Level2SceneExit, Level2SceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level2 Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level2SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level2SceneLoad(void)
{
	instance.mesh = MeshCreate();
	MeshBuildSpaceship(instance.mesh);
}

// Initialize the entities and variables used by the scene.
static void Level2SceneInit()
{
	instance.spaceship = EntityFactoryBuild("./Data/SpaceshipHoming.txt");

	if (instance.spaceship)
	{
		Sprite* sprite = EntityGetSprite(instance.spaceship);
		SpriteSetMesh(sprite, instance.mesh);
	}

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0, 0, 0 });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	Level2SceneMovementController(instance.spaceship);
	EntityUpdate(instance.spaceship, dt);

	if (DGL_Input_KeyTriggered('Z'))
		SpriteSetAlpha(EntityGetSprite(instance.spaceship), .5f);
	if (DGL_Input_KeyTriggered('X'))
		SpriteSetAlpha(EntityGetSprite(instance.spaceship), 1.f);
	if (DGL_Input_KeyTriggered('1'))
		SceneSystemSetNext(Level1SceneGetInstance());
	if (DGL_Input_KeyTriggered('2'))
		SceneSystemSetNext(Level2SceneGetInstance());
	if (DGL_Input_KeyTriggered('9'))
		SceneSystemSetNext(SandboxSceneGetInstance());
	if (DGL_Input_KeyTriggered('0'))
		SceneSystemRestart();	
}

// Render any objects associated with the scene.
void Level2SceneRender(void)
{
	EntityRender(instance.spaceship);
}

// Free any objects associated with the scene.
static void Level2SceneExit()
{
	EntityFree(&instance.spaceship);
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
	//MeshFree(&instance.mesh);
}

static void Level2SceneMovementController(Entity* entity)
{
	Physics* physics = EntityGetPhysics(entity);
	Transform* transform = EntityGetTransform(entity);

	if (entity && physics && transform)
	{
		Vector2D mousePosScreen = DGL_Input_GetMousePosition();
		Vector2D mousePos = DGL_Camera_ScreenCoordToWorld(&mousePosScreen);

		Vector2D translation = *TransformGetTranslation(transform);
		Vector2D* dir = calloc(1, sizeof(Vector2D));
		Vector2DSub(dir, &mousePos, &translation);
		Vector2DNormalize(dir, dir);
		TransformSetRotation(transform, Vector2DToAngleRad(dir));
		Vector2DScale(dir, dir, spaceshipSpeed);
		PhysicsSetVelocity(physics, dir);
		free(dir);
	}
}
