//------------------------------------------------------------------------------
//
// File Name:	DemoScene.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "DGL.h"

#include "DemoScene.h"
#include "Scene.h"
#include "SceneSystem.h"

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct DemoScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} DemoScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

// TODO: Declare Constants:


//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// TODO: Declare Variables:


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void DemoSceneLoad(void);
static void DemoSceneInit(void);
static void DemoSceneUpdate(float dt);
static void DemoSceneExit(void);
static void DemoSceneUnload(void);
static void DemoSceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static DemoScene instance =
{
	// Initialize the base structure:
	{ "Demo", DemoSceneLoad, DemoSceneInit, DemoSceneUpdate, DemoSceneRender, DemoSceneExit, DemoSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Demo Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* DemoSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void DemoSceneLoad(void)
{
	// TODO: Create Meshes:


	// TODO: Load/Create Textures:


}

// Initialize the entities and variables used by the scene.
static void DemoSceneInit()
{
	// TODO: Add code to set the following variables to their starting values.
	//   posCamera
	//   posSpaceship
	//   uvOffset
	//   alpha
	//   rotation


	// TODO: Set the background color and blend mode.


}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void DemoSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	// Update the scene.
	if (DGL_Window_HasFocus())
	{
		// TODO: Update the camera's position.


		// TODO: Update the triangular ("Spaceship") mesh's position.


		// TODO: Update the triangular ("Spaceship") mesh's Alpha value.


		// TODO: Update the Ball texture's UV offsets.


		// TODO: Update the rotation value.


		// TODO: Add code to restart the level when the ‘0’ key is triggered (when the key changes state from not pressed to pressed).


	}
}

// Render any objects associated with the scene.
void DemoSceneRender(void)
{
	// TODO: Update the camera's position every frame.


	// TODO: Display a simple, colored mesh.


	// TODO: Draw a simple, colored mesh with a red (50%) tint.


	// TODO: Draw a simple, textured mesh using the Ball texture.


	// TODO: Draw a simple, textured mesh using the 2x2 texture.


	// TODO: Draw a triangular, colored mesh.


	// TODO: Draw a 4-segment line strip.


}

// Free any objects associated with the scene.
static void DemoSceneExit()
{
}

// Unload any resources used by the scene.
static void DemoSceneUnload(void)
{
	// TODO: Free all meshes


	// TODO: Free all textures


}

