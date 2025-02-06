#include "helpers.h"



Mesh* createCube() {
    // Cube data
    // Vertex positions
    std::vector<Vertex> vertices = {
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 0: Bottom-left-back
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 1: Bottom-right-back
        {glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 2: Top-right-back
        {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 3: Top-left-back
        {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 4: Bottom-left-front
        {glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 5: Bottom-right-front
        {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 6: Top-right-front
        {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f)}, // 7: Top-left-front
    };

    // Indices
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

    // Assign colors to vertices
    {
        vertices[0].color = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[1].color = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[2].color = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[3].color = glm::vec3(1.0f, 1.0f, 0.0f);
        vertices[4].color = glm::vec3(1.0f, 0.0f, 1.0f);
        vertices[5].color = glm::vec3(0.0f, 1.0f, 1.0f);
        vertices[6].color = glm::vec3(0.5f, 0.75f, 1.0f);
        vertices[7].color = glm::vec3(1.0f, 0.5f, 0.25f);
    }
    

    // Create mesh
    Mesh* cube = new Mesh(vertices, indices);

    return cube;
}



// Function to draw the scene/level grid
void DrawGrid(float size, float step, Shader *shader) {
    std::vector<float> vertices;

    // Create vertices for the grid (lines)
    for (float i = -size; i <= size; i += step) {
        // Skip adding grid lines at the axis positions
        if (i == 0.0f)
        {
            // Half grid line in the negative direction of the rendered X axis
            vertices.push_back(-size);
            vertices.push_back(0.0f);
            vertices.push_back(i);

            vertices.push_back(0);
            vertices.push_back(0.0f);
            vertices.push_back(i);


            // Half grid line in the negative direction of the rendered Z axis
            vertices.push_back(i);
            vertices.push_back(0.0f);
            vertices.push_back(-size);

            vertices.push_back(i);
            vertices.push_back(0.0f);
            vertices.push_back(0);

            continue;
        }
        

        // Horizontal lines (parallel to X-axis)
        vertices.push_back(-size); // Start at the left
        vertices.push_back(0.0f);  // Y = 0
        vertices.push_back(i);     // Z = i

        vertices.push_back(size);  // End at the right
        vertices.push_back(0.0f);  // Y = 0
        vertices.push_back(i);     // Z = i

        // Vertical lines (parallel to Z-axis)
        vertices.push_back(i);     // X = i
        vertices.push_back(0.0f);  // Y = 0
        vertices.push_back(-size); // Start at the back

        vertices.push_back(i);     // X = i
        vertices.push_back(0.0f);  // Y = 0
        vertices.push_back(size);  // End at the front
    }

    // Create VAO, VBO for the grid
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Draw the grid (light gray color)
    shader->use();
    shader->setVec3("lineColor", glm::vec3(0.5f, 0.5f, 0.5f));
    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, vertices.size() / 3);

    // Draw Axis lines (X = Red, Y = Green, Z = Blue)
    std::vector<float> axisVertices;

    // X-axis (Red)
    // Start at the origin
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);

    // End at (size, 0, 0)
    axisVertices.push_back(size);
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);

    // Y-axis (Green)
    // Start at the origin
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);

    // End at (0, size, 0)
    axisVertices.push_back(0.0f);
    axisVertices.push_back(size);
    axisVertices.push_back(0.0f);

    // Z-axis (Blue)
    // Start at the origin
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);

    // End at (0, 0, size)
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);
    axisVertices.push_back(size);

    // Create VAO, VBO for the axis lines
    unsigned int axisVAO, axisVBO;
    glGenVertexArrays(1, &axisVAO);
    glGenBuffers(1, &axisVBO);

    glBindVertexArray(axisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, axisVertices.size() * sizeof(float), axisVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set line width
    glLineWidth(2.0f);


    // Draw X-axis (Red)
    shader->setVec3("lineColor", glm::vec3(1.0f, 0.0f, 0.0f));
    glDrawArrays(GL_LINES, 0, 2);

    // Draw Y-axis (Green)
    shader->setVec3("lineColor", glm::vec3(0.0f, 1.0f, 0.0f));
    glDrawArrays(GL_LINES, 2, 2);

    // Draw Z-axis (Blue)
    shader->setVec3("lineColor", glm::vec3(0.0f, 0.0f, 1.0f));
    glDrawArrays(GL_LINES, 4, 2);

    // Cleanup
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
