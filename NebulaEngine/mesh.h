#pragma once

#include "structs.h"
#include <vector>
#include <GL/glew.h>


class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Material material;


    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material);
    void Draw();

private:
    // Render data
    unsigned int VAO, VBO, IBO;

    void Setup();


};