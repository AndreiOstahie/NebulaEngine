#include "mesh.h"
#include <iostream>

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;

    // Identity model matrix
    modelMatrix = glm::mat4(1);

    // Set default shader if no other shader is provided
    Shader* shader = new Shader("../Shaders/VertexShader.glsl", "../Shaders/FragmentShader.glsl");
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

    // Identity model matrix
    modelMatrix = glm::mat4(1);

    // Set default shader if no other shader is provided
    Shader* shader = new Shader("../Shaders/VertexShader.glsl", "../Shaders/FragmentShader.glsl");
    this->shader = shader;

    // Perform mesh setup
    Setup();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material)
{
    this->vertices = vertices;
    this->indices = indices;
    this->material = material;

    // Identity model matrix
    modelMatrix = glm::mat4(1);

    // Set default shader if no other shader is provided
    Shader* shader = new Shader("../Shaders/VertexShader.glsl", "../Shaders/FragmentShader.glsl");
    this->shader = shader;

    // Perform mesh setup
    Setup();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Shader *shader)
{
    this->vertices = vertices;
    this->indices = indices;
    this->shader = shader;

    // Identity model matrix
    modelMatrix = glm::mat4(1);


    // Perform mesh setup
    Setup();
}


void Mesh::DrawWithShader(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, glm::vec3 color)
{
    // Use the mesh's defined shader
    glUseProgram(shader->ID);


    // Set MVP matrices uniforms
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "Model"), 1, GL_FALSE, glm::value_ptr(Model));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "View"), 1, GL_FALSE, glm::value_ptr(View));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "Projection"), 1, GL_FALSE, glm::value_ptr(Projection));

    // Set mesh color uniform
    glUniform3fv(glGetUniformLocation(shader->ID, "color"), 1, glm::value_ptr(color));

    // Render the mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::DrawWithPhongShader(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, glm::vec3 viewPos, const std::vector<PointLight>& pointLights)
{
    // Use the mesh's defined shader
    glUseProgram(shader->ID);

    // Set MVP matrices uniforms
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "Model"), 1, GL_FALSE, glm::value_ptr(Model));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "View"), 1, GL_FALSE, glm::value_ptr(View));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "Projection"), 1, GL_FALSE, glm::value_ptr(Projection));

    // Send the camera's view position as a uniform value (used for fragment lighting calculations)
    glUniform3fv(glGetUniformLocation(shader->ID, "viewPos"), 1, glm::value_ptr(viewPos));

    // Set material properties (diffuse, specular, shininess)
    glUniform3fv(glGetUniformLocation(shader->ID, "materialDiffuse"), 1, glm::value_ptr(material.diffuse));
    glUniform3fv(glGetUniformLocation(shader->ID, "materialSpecular"), 1, glm::value_ptr(material.specular));
    glUniform1f(glGetUniformLocation(shader->ID, "materialShininess"), material.shininess);

    // Set point light properties
    int numLights = std::min((int)pointLights.size(), MAX_LIGHTS);
    glUniform1i(glGetUniformLocation(shader->ID, "numLights"), numLights);

    for (int i = 0; i < numLights; i++) {
        std::string lightBase = "pointLights[" + std::to_string(i) + "]";
        glUniform3fv(glGetUniformLocation(shader->ID, (lightBase + ".position").c_str()), 1, glm::value_ptr(pointLights[i].position));
        glUniform3fv(glGetUniformLocation(shader->ID, (lightBase + ".color").c_str()), 1, glm::value_ptr(pointLights[i].color));
        glUniform1f(glGetUniformLocation(shader->ID, (lightBase + ".strength").c_str()), pointLights[i].strength);
    }

    // Render the mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



void Mesh::Setup()
{
    // Create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Load data into vertex and index buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    // Set the vertex attribute pointers
    // Position (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Normal (location = 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Texture coords (location = 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoords));

    // Vertex color attribute (location = 3)
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}


void Mesh::SetShader(Shader* shader)
{
    this->shader = shader;
    Setup();
}

