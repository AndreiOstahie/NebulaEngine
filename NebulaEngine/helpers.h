#pragma once
#include "mesh.h"


// Returns a basic cube mesh centered in (0, 0, 0)
Mesh* createCube();


// Draws the world grid, along with the X, Y and Z axes (red, green, blue) using lines
void DrawGrid(float size, float step, Shader* shader);
