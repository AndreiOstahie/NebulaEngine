#pragma once

#include "structs.h"
#include <vector>
#include <GL/glew.h>
#include "shader.h"


class Mesh {
public:
    // Mesh geometry data
    std::vector<Vertex> vertices;  // position, normal, textureCoords, color
    std::vector<unsigned int> indices;

    // Mesh visual elements
    std::vector<Texture> textures;
    Material material;
    Shader *shader;

    // Model matrix used for various transformations
    glm::mat4 modelMatrix;

    // Constructors
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Shader* shader);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);
    
    
    // Different mesh drawing methods (mostly differ by the uniform values sent to the shader and the vertex color attribute at location = 3)
    void DrawWithShader(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    void DrawWithPhongShader(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, glm::vec3 viewPos, const std::vector<PointLight>& pointLights);

    // Prepare buffers and arrays, handle bindings and send vertex attributes to the shader
    void Setup();

    // Sets the shader to be used when rendering the mesh
    void SetShader(Shader* shader);



private:
    // Render data
    unsigned int VAO, VBO, IBO;

    


};