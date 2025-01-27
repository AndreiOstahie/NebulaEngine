#pragma once
#include "mesh.h"


Mesh* createCube();
Mesh* createCubeWithShader();



void DrawGrid(float size, float step, Shader* shader);
