//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
// Author(s):	Xanna Fuller (xan.fuller)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "DGL.h"
#include "SpriteSource.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
typedef struct SpriteSource
{
	// The dimensions of the sprite sheet.
	// (Hint: These should be initialized to (1, 1).)
	int	numRows;
	int	numCols;

	// Pointer to a texture resource created using the DigiPen Graphics Library (DGL).
	const DGL_Texture* texture;

} SpriteSource;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
// Dynamically allocate a new SpriteSource object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: numRows and numCols should be initialized to 1.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
SpriteSource* SpriteSourceCreate()
{
	SpriteSource* output = (SpriteSource*) calloc(1, sizeof(SpriteSource));
	if (!output)
		return NULL;
	output->numCols = 1;
	output->numRows = 1;
	return output;
}

// Free the memory associated with a SpriteSource object.
// (NOTE: The DGL_Texture resource must be freed using DGL_Graphics_FreeTexture().)
// (NOTE: The SpriteSource object must be freed using free().
// (NOTE: The SpriteSource pointer must be set to NULL.)
// Params:
//	 spriteSource = Pointer to the SpriteSource pointer.
void SpriteSourceFree(SpriteSource** spriteSource)
{
	DGL_Graphics_FreeTexture(&(*spriteSource)->texture);
	free(*spriteSource);
	spriteSource = NULL;
}

// Load a texture from a file (may be an Col x Row sprite sheet).
// (NOTE: The folder path, "Assets/" should be prepended to the texture name before
//    opening the file.  The function sprintf_s can be used for this purpose.
//    https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l)
// Params:
//	 numCols = The number of columns in the sprite sheet.
//	 numRows = The number of rows in the sprite sheet.
//	 textureName = The name of the texture to be loaded.
void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName)
{
	if (!spriteSource)
		return;
	char path[128];
	sprintf_s(path, 128, "%s%s", "Assets/", textureName);
	spriteSource->numCols = numCols;
	spriteSource->numRows = numRows;
	spriteSource->texture = DGL_Graphics_LoadTexture(path);
}

// Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
// (Hint: Frame count = numCols * numRows.)
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
// Returns:
//	 If the SpriteSource pointer is valid,
//		then return the calculated frame count (numCols * numRows),
//		else return 0.
unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource)
{
	if (!spriteSource)
		return 0;

	return spriteSource->numCols * spriteSource->numRows;
}

// Returns the UV coordinates of the specified frame in a sprite sheet.
// (Hint: Refer to the Week 2 lecture slides for the correct calculations.)
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
//	 frameIndex = A frame index within a sprite sheet.
//   u = Pointer to a float to contain the U coordinate. 
//   v = Pointer to a float to contain the V coordinate. 
void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, float* u, float* v)
{
	if (!spriteSource)
		return;
	float uSize = 1.f / spriteSource->numCols;
	float vSize = 1.f / spriteSource->numRows;

	*u = uSize * ( frameIndex % spriteSource->numCols );
	*v = vSize * ( frameIndex / spriteSource->numRows );
}

// Sets a SpriteSource texture for rendering.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
void SpriteSourceSetTexture(const SpriteSource* spriteSource)
{
	if (spriteSource)
	{
		DGL_Graphics_SetTexture(spriteSource->texture);
	}
}

// Sets the texture UV offsets for rendering.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex)
{
	if (spriteSource)
	{
		float u, v;
		SpriteSourceGetUV(spriteSource, frameIndex, &u, &v);
		DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { u, v });
	}
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

