#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>
#include "mesh.h"

class MeshLoader {

public:
	Mesh LoadMesh(const std::string& path, bool isZUp);

private:
	Mesh ProcessMesh(aiMesh* mesh, aiMaterial* aiMaterial, bool isZUp);
};