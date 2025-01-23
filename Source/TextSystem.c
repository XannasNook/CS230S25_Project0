//------------------------------------------------------------------------------
//
// File Name:	TextSystem.c
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
#include "math.h"

#include "BaseSystem.h"
#include "TextSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct TextSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.

} TextSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static DGL_Mesh* CreateMesh(float width, float height);

//  System-specific State functions:
static bool TextSystemInit(void);
static void TextSystemUpdate(float dt);
static void TextSystemRender(void);
static void TextSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static TextSystem instance =
{
	{ "TextSystem", TextSystemInit, TextSystemUpdate, TextSystemRender, TextSystemExit},
};

DGL_Texture* fontSheet;
DGL_Mesh* textMesh;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Text System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* TextSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

void TextEffect(const char* string, DGL_Vec2 worldPos, float scale)
{
}

void RenderText(const char* string, DGL_Vec2 worldPos, float scale)
{
	if (*string == 0)
		return;

	int count = 0;
	float offset = 0;

	while (1)
	{
		char curChar = *(string + count);

		if (curChar == 0)
			break;

		float tempOffset = offset;
		DGL_Mesh* mesh = CreateMesh(1, 1);
		DGL_Vec2 uv = { 0, 0 };

		switch (curChar)
		{
		case 'A':
			uv = (DGL_Vec2) { 3, 2 };
			offset += scale * 14;
			break;
		case 'B':
			uv = (DGL_Vec2) { 4, 2 };
			offset += scale * 15;
			break;
		case 'C':
			uv = (DGL_Vec2) { 5, 2 };
			offset += scale * 17;
			break;
		case 'D':
			uv = (DGL_Vec2) { 6, 2 };
			offset += scale * 15;
			break;
		case 'E':
			uv = (DGL_Vec2) { 7, 2 };
			offset += scale * 12;
			break;
		case 'F':
			uv = (DGL_Vec2) { 8, 2 };
			offset += scale * 16;
			break;
		case 'G':
			uv = (DGL_Vec2) { 9, 2 };
			offset += scale * 16;
			break;
		case 'H':
			uv = (DGL_Vec2) { 10, 2 };
			offset += scale * 13;
			break;
		case 'I':
			uv = (DGL_Vec2) { 11, 2 };
			offset += scale * 6;
			break;
		case 'J':
			uv = (DGL_Vec2) { 12, 2 };
			offset += scale * 10;
			break;
		case 'K':
			uv = (DGL_Vec2) { 13, 2 };
			offset += scale * 17;
			break;
		case 'L':
			uv = (DGL_Vec2) { 14, 2 };
			offset += scale * 14;
			break;
		case 'M':
			uv = (DGL_Vec2) { 0, 3 };
			offset += scale * 19;
			break;
		case 'N':
			uv = (DGL_Vec2) { 1, 3 };
			offset += scale * 18;
			break;
		case 'O':
			uv = (DGL_Vec2) { 2, 3 };
			offset += scale * 17;
			break;
		case 'P':
			uv = (DGL_Vec2) { 3, 3 };
			offset += scale * 17;
			break;
		case 'Q':
			uv = (DGL_Vec2) { 4, 3 };
			offset += scale * 17;
			break;
		case 'R':
			uv = (DGL_Vec2) { 5, 3 };
			offset += scale * 16;
			break;
		case 'S':
			uv = (DGL_Vec2) { 6, 3 };
			offset += scale * 15;
			break;
		case 'T':
			uv = (DGL_Vec2) { 7, 3 };
			offset += scale * 16;
			break;
		case 'U':
			uv = (DGL_Vec2) { 8, 3 };
			offset += scale * 18;
			break;
		case 'V':
			uv = (DGL_Vec2) { 9, 3 };
			offset += scale * 17;
			break;
		case 'W':
			tempOffset += scale * 4;
			uv = (DGL_Vec2) { 10, 3 };
			offset += scale * 23;
			break;
		case 'X':
			uv = (DGL_Vec2) { 11, 3 };
			offset += scale * 17;
			break;
		case 'Y':
			uv = (DGL_Vec2) { 12, 3 };
			offset += scale * 14;
			break;
		case 'Z':
			uv = (DGL_Vec2) { 13, 3 };
			offset += scale * 13;
			break;
		case 'a':
			uv = (DGL_Vec2) { 5, 4 };
			offset += scale * 12;
			break;
		case 'b':
			uv = (DGL_Vec2) { 6, 4 };
			offset += scale * 11;
			break;
		case 'c':
			uv = (DGL_Vec2) { 7, 4 };
			offset += scale * 12;
			break;
		case 'd':
			uv = (DGL_Vec2) { 8, 4 };
			offset += scale * 12;
			break;
		case 'e':
			uv = (DGL_Vec2) { 9, 4 };
			offset += scale * 12;
			break;
		case 'f':
			tempOffset -= 2;
			uv = (DGL_Vec2) { 10, 4 };
			offset += scale * 10;
			break;
		case 'g':
			uv = (DGL_Vec2) { 11, 4 };
			offset += scale * 13;
			break;
		case 'h':
			uv = (DGL_Vec2) { 12, 4 };
			offset += scale * 13;
			break;
		case 'i':
			tempOffset -= 3;
			uv = (DGL_Vec2) { 13, 4 };
			offset += scale * 10;
			break;
		case 'j':
			tempOffset -= 7;
			uv = (DGL_Vec2) { 14, 4 };
			offset += scale * 5;
			break;
		case 'k':
			uv = (DGL_Vec2) { 0, 5 };
			offset += scale * 13;
			break;
		case 'l':
			tempOffset -= 2;
			uv = (DGL_Vec2) { 1, 5 };
			offset += scale * 13;
			break;
		case 'm':
			uv = (DGL_Vec2) { 2, 5 };
			offset += scale * 13;
			break;
		case 'n':
			uv = (DGL_Vec2) { 3, 5 };
			offset += scale * 13;
			break;
		case 'o':
			uv = (DGL_Vec2) { 4, 5 };
			offset += scale * 13;
			break;
		case 'p':
			uv = (DGL_Vec2) { 5, 5 };
			offset += scale * 12;
			break;
		case 'q':
			uv = (DGL_Vec2) { 6, 5 };
			offset += scale * 11;
			break;
		case 'r':
			uv = (DGL_Vec2) { 7, 5 };
			offset += scale * 11;
			break;
		case 's':
			uv = (DGL_Vec2) { 8, 5 };
			offset += scale * 10;
			break;
		case 't':
			uv = (DGL_Vec2) { 9, 5 };
			offset += scale * 11;
			break;
		case 'u':
			uv = (DGL_Vec2) { 10, 5 };
			offset += scale * 13;
			break;
		case 'v':
			uv = (DGL_Vec2) { 11, 5 };
			offset += scale * 13;
			break;
		case 'w':
			uv = (DGL_Vec2) { 12, 5 };
			offset += scale * 13;
			break;
		case 'x':
			uv = (DGL_Vec2) { 13, 5 };
			offset += scale * 13;
			break;
		case 'y':
			uv = (DGL_Vec2) { 14, 5 };
			offset += scale * 13;
			break;
		case 'z':
			uv = (DGL_Vec2) { 0, 6 };
			offset += scale * 13;
			break;
		case '0':
			uv = (DGL_Vec2) { 1, 1 };
			offset += scale * 13;
			break;
		case '1':
			uv = (DGL_Vec2) { 2, 1 };
			offset += scale * 13;
			break;
		case '2':
			uv = (DGL_Vec2) { 3, 1 };
			offset += scale * 12;
			break;
		case '3':
			uv = (DGL_Vec2) { 4, 1 };
			offset += scale * 14;
			break;
		case '4':
			uv = (DGL_Vec2) { 5, 1 };
			offset += scale * 13;
			break;
		case '5':
			uv = (DGL_Vec2) { 6, 1 };
			offset += scale * 13;
			break;
		case '6':
			uv = (DGL_Vec2) { 7, 1 };
			offset += scale * 13;
			break;
		case '7':
			uv = (DGL_Vec2) { 8, 1 };
			offset += scale * 13;
			break;
		case '8':
			uv = (DGL_Vec2) { 9, 1 };
			offset += scale * 13;
			break;
		case '9':
			uv = (DGL_Vec2) { 10, 1 };
			offset += scale * 13;
			break;
		case '!':
			uv = (DGL_Vec2) { 1, 0 };
			offset += scale * 15;
			break;
		case '\'':
			uv = (DGL_Vec2) { 7, 0 };
			offset += scale * 15;
			break;
		case '&':
			uv = (DGL_Vec2) { 6, 0 };
			offset += scale * 15;
			break;
		case '*':
			uv = (DGL_Vec2) { 10, 0 };
			offset += scale * 15;
			break;
		case ')':
			uv = (DGL_Vec2) { 9, 0 };
			offset += scale * 11;
			break;
		case '(':
			uv = (DGL_Vec2) { 8, 0 };
			offset += scale * 15;
			break;
		case ':':
			uv = (DGL_Vec2) { 11, 1 };
			offset += scale * 15;
			break;
		case ',':
			uv = (DGL_Vec2) { 12, 0 };
			offset += scale * 15;
			break;
		case '=':
			uv = (DGL_Vec2) { 14, 1 };
			offset += scale * 15;
			break;
		case '-':
			uv = (DGL_Vec2) { 13, 0 };
			offset += scale * 15;
			break;
		case '.':
			uv = (DGL_Vec2) { 14, 0 };
			offset += scale * 15;
			break;
		case '"':
			uv = (DGL_Vec2) { 2, 0 };
			offset += scale * 15;
			break;
		case '?':
			uv = (DGL_Vec2) { 1, 2 };
			offset += scale * 15;
			break;
		case ';':
			uv = (DGL_Vec2) { 12, 1 };
			offset += scale * 15;
			break;
		case '/':
			uv = (DGL_Vec2) { 0, 1 };
			offset += scale * 15;
			break;
		case '_':
			uv = (DGL_Vec2) { 3, 4 };
			offset += scale * 15;
			break;
		default:
			offset += scale * 15;
			DGL_Graphics_FreeMesh(&mesh);
			count++;
			continue;
		}

		//offset += 15;
		count++;

		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		DGL_Graphics_SetTexture(fontSheet);
		DGL_Graphics_SetCB_Alpha(1.0f);
		DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { (1.f / 15.f) * uv.x, (1.f / 7.f) * uv.y });
		DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
		DGL_Graphics_SetCB_ZLayer(1 / (float)count);
		DGL_Graphics_SetCB_TransformData(&(DGL_Vec2) { worldPos.x + tempOffset, worldPos.y }, & (DGL_Vec2) { 30 * scale, 30 * scale }, 0.f);
		DGL_Graphics_DrawMesh(mesh, DGL_DM_TRIANGLELIST);

		DGL_Graphics_FreeMesh(&mesh);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

DGL_Mesh* CreateMesh(float width, float height)
{
	// Adjust the texture coordinates based on the animation frames
	float uWidth = 1.0f / 15;
	float vHeight = 1.0f / 7;

	DGL_Graphics_StartMesh();

	DGL_Vec2 pos = { 0, 0 };
	DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
	DGL_Vec2 uv = { 0.0f, vHeight };                // Bottom left coordinate
	DGL_Graphics_AddVertex(&pos, &color, &uv);

	pos = (DGL_Vec2){ 0, height };
	uv = (DGL_Vec2){ 0.0f, 0.0f };                  // Top left coordinate
	DGL_Graphics_AddVertex(&pos, &color, &uv);

	pos = (DGL_Vec2){ width, height };
	uv = (DGL_Vec2){ uWidth, 0.0f };                // Top right coordinate
	DGL_Graphics_AddVertex(&pos, &color, &uv);

	pos = (DGL_Vec2){ 0, 0 };
	uv = (DGL_Vec2){ 0.0f, vHeight };               // Bottom left coordinate
	DGL_Graphics_AddVertex(&pos, &color, &uv);

	pos = (DGL_Vec2){ width, height };
	uv = (DGL_Vec2){ uWidth, 0.0f };                // Top right coordinate
	DGL_Graphics_AddVertex(&pos, &color, &uv);

	pos = (DGL_Vec2){ width, 0 };
	uv = (DGL_Vec2){ uWidth, vHeight };             // Bottom right coordinate
	DGL_Graphics_AddVertex(&pos, &color, &uv);

	return DGL_Graphics_EndMesh();
}

// Initialize the Text System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool TextSystemInit(void)
{
	fontSheet = DGL_Graphics_LoadTexture("Assets/Font.png");

	// Return false if the system was NOT initialized successfully.

	// Return true if the system was initialized successfully.
	return true;
}

// Update the Text System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void TextSystemUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
}

// Render any objects associated with the Stub System.
static void TextSystemRender(void)
{
}

// Shutdown the Stub System.
//   (HINT: Free any allocated resources and/or close any opened files).
static void TextSystemExit(void)
{
	DGL_Graphics_FreeTexture(&fontSheet);
}

