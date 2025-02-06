#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>
#include "mesh.h"

class MeshLoader {

public:
	// Imports a mesh from a file using assimp
	// "isZUp" is used to adjust the vertex positions and normals of the mesh in case the file format uses the Z axis as the Up vector (this engine uses the Y axis)
	Mesh LoadMesh(const std::string& path, bool isZUp);

private:
	// Processes the imported mesh's data, then stores and returns it in a Mesh object
	// "isZUp" is used to adjust the vertex positions and normals of the mesh in case the file format uses the Z axis as the Up vector (this engine uses the Y axis)
	Mesh ProcessMesh(aiMesh* mesh, aiMaterial* aiMaterial, bool isZUp);
};