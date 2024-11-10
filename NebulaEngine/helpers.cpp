#include "helpers.h"



Mesh* createCube() {
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
    Mesh* cube = new Mesh(vertices, indices, textures, material);

    return cube;
}





// Draw a grid on the XZ plane
void drawGrid(int gridSize, float spacing, const glm::vec3& color)
{
    glDisable(GL_DEPTH_TEST); // Optionally disable depth testing for better visibility
    glLineWidth(1.0f);        // Set line width for the grid lines

    glBegin(GL_LINES);        // Begin drawing lines

    glColor3f(color.r, color.g, color.b); // Set grid line color

    // Draw lines along the X axis
    for (int i = -gridSize; i <= gridSize; ++i)
    {
        glVertex3f(i * spacing, 0.0f, -gridSize * spacing);
        glVertex3f(i * spacing, 0.0f, gridSize * spacing);
    }

    // Draw lines along the Z axis
    for (int j = -gridSize; j <= gridSize; ++j)
    {
        glVertex3f(-gridSize * spacing, 0.0f, j * spacing);
        glVertex3f(gridSize * spacing, 0.0f, j * spacing);
    }

    glEnd();                 // End drawing lines
    glEnable(GL_DEPTH_TEST); // Re-enable depth testing if it was disabled
}