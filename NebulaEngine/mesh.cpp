#include "mesh.h"
#include <iostream>

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;

    // Set default shader if no other shader is provided
    Shader* shader = new Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
    this->shader = shader;

    // Perform mesh setup
    Setup();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->material = material;

    // Set default shader if no other shader is provided
    Shader* shader = new Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
    this->shader = shader;

    // Perform mesh setup
    Setup();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Shader *shader)
{
    this->vertices = vertices;
    this->indices = indices;
    this->shader = shader;

    // Perform mesh setup
    Setup();
}

void Mesh::Draw()
{
    // std::cout << "Drawing mesh..." << std::endl;

    // Bind textures
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Activate texture unit
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // Draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Unbind textures
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Reset to default texture unit
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::DrawWithShader(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection)
{
    // Render
    glUseProgram(shader->ID);


    // Set uniforms
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "Model"), 1, GL_FALSE, glm::value_ptr(Model));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "View"), 1, GL_FALSE, glm::value_ptr(View));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "Projection"), 1, GL_FALSE, glm::value_ptr(Projection));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::Setup()
{
    std::cout << "Setup mesh..." << std::endl;

    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoords));

    glBindVertexArray(0);
}

void Mesh::SetShader(Shader* shader)
{
    this->shader = shader;
    Setup();
}

