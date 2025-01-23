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

#include "BaseSystem.h"
#include "TypeWriterSystem.h"

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

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the TypeWriter System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool TypeWriterSystemInit(void)
{
	// Return false if the system was NOT initialized successfully.

	// Return true if the system was initialized successfully.
	return true;
}

// Update the TypeWriter System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void TypeWriterSystemUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
}

// Render any objects associated with the TypeWriter System.
static void TypeWriterSystemRender(void)
{
}

// Shutdown the TypeWriter System.
//   (HINT: Free any allocated resources and/or close any opened files).
static void TypeWriterSystemExit(void)
{
}

