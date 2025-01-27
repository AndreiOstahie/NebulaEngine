#pragma once

#include "structs.h"
#include <vector>
#include <GL/glew.h>
#include "shader.h"


class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Material material;
    Shader *shader;

    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Shader* shader);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material);
    
    
    void Draw();
    void DrawWithShader(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection);
    void Setup();
    void SetShader(Shader* shader);



private:
    // Render data
    unsigned int VAO, VBO, IBO;

    


};