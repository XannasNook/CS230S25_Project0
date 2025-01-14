//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.c
// Author(s):	Xanna Fuller (xan.fuller)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Vector2D.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "SandboxScene.h"
#include "Stream.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SandboxScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} SandboxScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void SandboxSceneLoad(void);
static void SandboxSceneInit(void);
static void SandboxSceneUpdate(float dt);
static void SandboxSceneExit(void);
static void SandboxSceneUnload(void);
static void SandboxSceneRender(void);
static void SandboxSceneTraceFloat(const char* text, float f);
static void SandboxSceneTraceVector(const char* text, const Vector2D* v);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SandboxScene instance =
{
	// Initialize the base structure:
	{ "Sandbox", SandboxSceneLoad, SandboxSceneInit, SandboxSceneUpdate, SandboxSceneRender, SandboxSceneExit, SandboxSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Sandbox Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* SandboxSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void SandboxSceneLoad(void)
{
}

// Initialize the entities and variables used by the scene.
static void SandboxSceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SandboxSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	Stream stream = StreamOpen("Data/VectorTests.txt");

	if (stream)
	{
		Vector2D vectorBase;
		Vector2D* vec = &vectorBase;
		Vector2DZero(vec);
		SandboxSceneTraceVector("Vector2DZero", vec);
		Vector2DSet(vec, 1.5f, 1.f);
		SandboxSceneTraceVector("Vector2DSet", vec);
		Vector2DNeg(vec, vec);
		SandboxSceneTraceVector("Vector2DNeg", vec);
		Vector2DAdd(vec, vec, vec);
		SandboxSceneTraceVector("Vector2DAdd", vec);
		Vector2DSub(vec, vec, vec);
		SandboxSceneTraceVector("Vector2DSub", vec);
		StreamReadVector2D(stream, vec);
		SandboxSceneTraceVector("StreamReadVector2D", vec);
		Vector2DNormalize(vec, vec);
		SandboxSceneTraceVector("Vector2DNormalize", vec);
		float scale = StreamReadFloat(stream);
		SandboxSceneTraceFloat("StreamReadFloat", scale);
		Vector2DScale(vec, vec, scale);
		SandboxSceneTraceVector("Vector2DScale", vec);
		Vector2DScaleAdd(vec, vec, scale, vec);
		SandboxSceneTraceVector("Vector2DScaleAdd", vec);
		Vector2DScaleSub(vec, vec, scale, vec);
		SandboxSceneTraceVector("Vector2DScaleSub", vec);
		SandboxSceneTraceFloat("Vector2DLength", Vector2DLength(vec));
		SandboxSceneTraceFloat("Vector2DSquareLength", Vector2DSquareLength(vec));
		Vector2D vectorBase1, vectorBase2;
		Vector2D* v1 = &vectorBase1;
		Vector2D* v2 = &vectorBase2;
		StreamReadVector2D(stream, v1);
		SandboxSceneTraceVector("StreamReadVector2D", v1);
		StreamReadVector2D(stream, v2);
		SandboxSceneTraceVector("StreamReadVector2D", v2);
		SandboxSceneTraceFloat("Vector2DDistance", Vector2DDistance(v1, v2));
		SandboxSceneTraceFloat("Vector2DSquareDistance", Vector2DSquareDistance(v1, v2));
		SandboxSceneTraceFloat("Vector2DDotProduct", Vector2DDotProduct(v1,v2));
		Vector2D* v = &vectorBase;
		float angle = StreamReadFloat(stream);
		SandboxSceneTraceFloat("SreamReadFloat", angle);
		Vector2DFromAngleDeg(v, angle);
		SandboxSceneTraceVector("Vector2DFromAngleDeg", v);
		angle = StreamReadFloat(stream);
		SandboxSceneTraceFloat("SreamReadFloat", angle);
		Vector2DFromAngleRad(v, angle);
		SandboxSceneTraceVector("Vector2DFromAngleRad", v);
		SandboxSceneTraceFloat("Vector2DToAngleRad", Vector2DToAngleRad(v));
		StreamClose(&stream);
	}

	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	SceneSystemSetNext(NULL);
}

// Render any objects associated with the scene.
void SandboxSceneRender(void)
{
}

// Free any objects associated with the scene.
static void SandboxSceneExit()
{
}

// Unload any resources used by the scene.
static void SandboxSceneUnload(void)
{
}

static void SandboxSceneTraceFloat(const char* text, float f)
{
	TraceMessage("Vector Test: %s = %f", text, f);
}

static void SandboxSceneTraceVector(const char* text, const Vector2D* v)
{
	TraceMessage("Vector Test: %s = [%f, %f]", text, v->x, v->y);
}