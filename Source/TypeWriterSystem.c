//------------------------------------------------------------------------------
//
// File Name:	TypeWriterSystem.c
// Author(s):	Xanna Fuller (xan.fuller)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Windows.h>
#include "DGL.h"

#include "BaseSystem.h"
#include "TypeWriterSystem.h"
#include "TextSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct TypeWriterSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.
	char* curWritten;

} TypeWriterSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool TypeWriterSystemInit(void);
static void TypeWriterSystemUpdate(float dt);
static void TypeWriterSystemRender(void);
static void TypeWriterSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static TypeWriterSystem instance =
{
	{ "TypeWriterSystem", TypeWriterSystemInit, TypeWriterSystemUpdate, TypeWriterSystemRender, TypeWriterSystemExit},
};

float timer;
char curWritten[1024];
char toWrite[1024];
int pointer;
DGL_Vec2 position;
float textScale;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the TypeWriter System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* TypeWriterSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

void SetTypeWriter(const char* str, DGL_Vec2 pos, float scale)
{
	strcpy_s(toWrite, _countof(toWrite), str);
	strcpy_s(curWritten, _countof(curWritten), "");
	position = pos;
	textScale = scale;
	timer = 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the TypeWriter System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool TypeWriterSystemInit(void)
{
	// Return false if the system was NOT initialized successfully.
	timer = 0;
	curWritten[0] = 0;
	toWrite[0] = 0;

	// Return true if the system was initialized successfully.
	return true;
}

// Update the TypeWriter System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void TypeWriterSystemUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	if (strncmp(curWritten, toWrite, sizeof(toWrite)))
	{
		if (timer < .005f)
		{
			timer += dt;
			return;
		}

		char character = toWrite[pointer];
		if (character)
		{
			curWritten[pointer] = character;
			curWritten[pointer + 1] = 0;
			pointer++;
		}
		timer = 0;
	}
}

// Render any objects associated with the TypeWriter System.
static void TypeWriterSystemRender(void)
{
	if (curWritten)
		RenderText(curWritten, position, textScale);
}

// Shutdown the TypeWriter System.
//   (HINT: Free any allocated resources and/or close any opened files).
static void TypeWriterSystemExit(void)
{
}

