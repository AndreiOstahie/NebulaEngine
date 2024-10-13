#pragma once
#include "libs.h"
#include "mesh.h"


Mesh createCube() {
    // Cube data
    std::vector<Vertex> vertices = {
        // Positions
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 0: Bottom-left-back
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 1: Bottom-right-back
        {glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 2: Top-right-back
        {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 3: Top-left-back
        {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 4: Bottom-left-front
        {glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 5: Bottom-right-front
        {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 6: Top-right-front
        {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 7: Top-left-front
    };
    std::vector<unsigned int> indices = {
        // Front face
        4, 5, 6,
        4, 6, 7,

        // Back face
        0, 1, 2,
        0, 2, 3,

        // Left face
        0, 4, 7,
        0, 7, 3,

        // Right face
        1, 5, 6,
        1, 6, 2,

        // Top face
        3, 2, 6,
        3, 6, 7,

        // Bottom face
        0, 1, 5,
        0, 5, 4
    };
    std::vector<Texture> textures = {};

    // Materialaterial
    Material material;
    material.diffuse = glm::vec3(1.0f, 0.5f, 0.3f);
    material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    material.shininess = 10.0f;

    // Create mesh
    Mesh cube(vertices, indices, textures, material);

    return cube;
}