//------------------------------------------------------------------------------
//
// File Name:	Mesh.c
// Author(s):	Xanna Fuller (xan.fuller)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "DGL.h"
#include "Mesh.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Mesh
{
	char name[32];

	const DGL_Mesh* meshResource;

	DGL_DrawMode drawMode;
} Mesh;

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

// Dynamically allocate a new Mesh object but leave it empty.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the mesh was created successfully,
//	   then return a pointer to the created Mesh,
//	   else return NULL.
Mesh* MeshCreate()
{
	Mesh* output = (Mesh*) calloc(1, sizeof(Mesh));
	if (!output)
		return NULL;
	return output;
}

// Build a quadrilateral mesh and store it in the specified Mesh object.
// (NOTE: The DGL_Mesh object must be created using DGL_Graphics_StartMesh,
//    DGL_Graphics_AddTriangle, and DGL_Graphics_EndMesh.)
// (NOTE: The Mesh name can be stored using strcpy_s(). For example:
//    strcpy_s(mesh->name, _countof(mesh->name), name); )
// (NOTE: The drawMode should be set to DGL_DM_TRIANGLELIST.)
// Params:
//   mesh = Pointer to an existing, empty Mesh object.
//	 xHalfSize = The X half-size of the mesh.
//	 yHalfSize = The Y half-size of the mesh.
//   uSize = The U size of the mesh, relative to texture coordinates (0.0 .. 1.0).
//   vSize = The V size of the mesh, relative to texture coordinates (0.0 .. 1.0).
//	 name = A name for the mesh.
void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	if (!mesh)
		return;
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2) { -xHalfSize, -yHalfSize }, &(DGL_Color) { 0, 0, 0, 0 }, &(DGL_Vec2) { 0, vSize },
		&(DGL_Vec2) { xHalfSize, yHalfSize }, &(DGL_Color) { 0, 0, 0, 0 }, &(DGL_Vec2) { uSize, 0 },
		&(DGL_Vec2) { xHalfSize, -yHalfSize }, &(DGL_Color) { 0, 0, 0, 0 }, &(DGL_Vec2) { uSize, vSize }
	);
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2) { -xHalfSize, -yHalfSize }, &(DGL_Color) { 0, 0, 0, 0 }, &(DGL_Vec2) { 0, vSize },
		&(DGL_Vec2) { -xHalfSize, yHalfSize }, &(DGL_Color) { 0, 0, 0, 0 }, &(DGL_Vec2) { 0, 0 },
		&(DGL_Vec2) { xHalfSize, yHalfSize }, &(DGL_Color) { 0, 0, 0, 0 }, &(DGL_Vec2) { uSize, 0 }
	);
	mesh->meshResource = DGL_Graphics_EndMesh();
	strcpy_s(mesh->name, _countof(mesh->name), name);
	mesh->drawMode = DGL_DM_TRIANGLELIST;
}

// Build a "spaceship" mesh and store it in the specified Mesh object.
// (NOTE: This must be a "unit"-sized triangular mesh with the same characteristics as
//    the "triangular, colored mesh" created in DemoScene.c.)
// (NOTE: The DGL_Mesh object must be created using DGL_Graphics_StartMesh,
//    DGL_Graphics_AddTriangle, and DGL_Graphics_EndMesh.)
// (NOTE: The Mesh name can be stored using strcpy_s().)
// (NOTE: The drawMode should be set to DGL_DM_TRIANGLELIST.)
// Params:
//   mesh = Pointer to an existing, empty Mesh object.
void MeshBuildSpaceship(Mesh* mesh)
{
	if (!mesh)
		return;
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		& (DGL_Vec2) { 0.5f, 0.0f }, &(DGL_Color) { 1, 1, 0, 1 }, & (DGL_Vec2) { 0.0f, 0.0f },
		& (DGL_Vec2) { -0.5f, -0.5f }, &(DGL_Color) { 1, 0, 0, 1}, & (DGL_Vec2) { 0.0f, 0.0f },
		& (DGL_Vec2) { -0.5f, 0.5f }, &(DGL_Color) { 1, 0, 0, 1}, & (DGL_Vec2){ 0.0f, 0.0f });
	mesh->meshResource = DGL_Graphics_EndMesh();
	strcpy_s(mesh->name, _countof(mesh->name), "Spaceship");
	mesh->drawMode = DGL_DM_TRIANGLELIST;
}

// Render a mesh.
// (NOTE: This is done using DGL_Graphics_DrawMesh().)
// Params:
//   mesh = Pointer to a Mesh to be rendered.
void MeshRender(const Mesh* mesh)
{
	if (!mesh)
		return;
	DGL_Graphics_DrawMesh(mesh->meshResource, mesh->drawMode);
}

// Free the memory associated with a mesh.
// (NOTE: The DGL_Mesh resource must be freed using DGL_Graphics_FreeMesh().)
// (NOTE: The Mesh object must be freed using free().
// (NOTE: The Mesh pointer must be set to NULL.)
// Params:
//   mesh = Pointer to the Mesh pointer.
void MeshFree(Mesh** mesh)
{
	DGL_Graphics_FreeMesh(&(*mesh)->meshResource);
	free(*mesh);
	mesh = NULL;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

