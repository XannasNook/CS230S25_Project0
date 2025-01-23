//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
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

#include "SceneSystem.h"
#include "DemoScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const float groundHeight = -150.f;
static const float moveVelocity = 500.f;
static const float jumpVelocity = 1000.f;
static const Vector2D gravityNormal = { 0.f, -1500.f };
static const Vector2D gravityNone = { 0.f, 0.f };

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;

	Mesh* mesh;
	SpriteSource* spriteSource;
	Entity* entity;
} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);
static void Level1SceneMovementController(Entity* entity);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables:
	.numLives = 0
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level1 Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level1SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{
	Stream stream = StreamOpen("Data/Level1_Lives.txt");
	if (stream)
	{
		instance.numLives = StreamReadInt(stream);
		StreamClose(&stream);
	}
	
	instance.mesh = MeshCreate();
	MeshBuildQuad(instance.mesh, .5f, .5f, 1, 1, "Mesh1x1");
	instance.spriteSource = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.spriteSource, 1, 1, "PlanetTexture.png");
}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit()
{
	instance.entity = EntityFactoryBuild("./Data/PlanetJump.txt");
	if (instance.entity)
	{
		Sprite* sprite = EntityGetSprite(instance.entity);
		SpriteSetMesh(sprite, instance.mesh);
		SpriteSetSpriteSource(sprite, instance.spriteSource);
		SpriteSetFrame(sprite, 0);
	}

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 1, 1, 1 });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	Level1SceneMovementController(instance.entity);
	EntityUpdate(instance.entity, dt);

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
void Level1SceneRender(void)
{
	EntityRender(instance.entity);
}

// Free any objects associated with the scene.
static void Level1SceneExit()
{
	EntityFree(&instance.entity);
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	//SpriteSourceFree(&instance.spriteSource);
	//MeshFree(&instance.mesh);
}

static void Level1SceneMovementController(Entity* entity)
{
	Physics* physics = EntityGetPhysics(entity);
	Transform* transform = EntityGetTransform(entity);

	if (entity && physics && transform)
	{
		Vector2D velocity = *PhysicsGetVelocity(physics);
		Vector2D acceleration = *PhysicsGetAcceleration(physics);

		if (DGL_Input_KeyDown(VK_LEFT))
			velocity.x = -moveVelocity;
		else if (DGL_Input_KeyDown(VK_RIGHT))
			velocity.x = moveVelocity;
		else
			velocity.x = 0;

		if (DGL_Input_KeyTriggered(VK_UP))
		{
			velocity.y = jumpVelocity;
			acceleration = gravityNormal;
		}

		Vector2D translation = *TransformGetTranslation(transform);
		if (translation.y < groundHeight)
		{
			translation.y = groundHeight;
			velocity.y = 0;
			acceleration = gravityNone;
			instance.numLives--;
			if (instance.numLives <= 0)
				SceneSystemSetNext(Level2SceneGetInstance());
		}

		PhysicsSetVelocity(physics, &velocity);
		PhysicsSetAcceleration(physics, &acceleration);
	}
}

