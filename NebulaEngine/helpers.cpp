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
    


    //std::vector<Texture> textures = {};

    //// Materialaterial
    //Material material;
    //material.diffuse = glm::vec3(1.0f, 0.5f, 0.3f);
    //material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    //material.shininess = 10.0f;

    //// Create mesh
    //Mesh* cube = new Mesh(vertices, indices, textures, material);


 

    // Create mesh
    Mesh* cube = new Mesh(vertices, indices);


    return cube;
}






Mesh* createCubeWithShader() {
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
    
    Shader* shader = new Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

    // Create mesh
    Mesh* cube = new Mesh(vertices, indices, shader);

    return cube;
}





// Function to draw a grid
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
    shader->setVec3("lineColor", glm::vec3(0.5f, 0.5f, 0.5f)); // Grid color (light gray)
    glLineWidth(1.0f);  // Set line width
    glDrawArrays(GL_LINES, 0, vertices.size() / 3);  // Draw the grid lines

    // Draw Axis lines (X = Red, Y = Green, Z = Blue)
    std::vector<float> axisVertices;

    // X-axis (Red)
    axisVertices.push_back(0.0f);  // Start at the origin
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);

    axisVertices.push_back(size);  // End at (size, 0, 0)
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);

    // Y-axis (Green)
    axisVertices.push_back(0.0f);  // Start at the origin
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);

    axisVertices.push_back(0.0f);  // End at (0, size, 0)
    axisVertices.push_back(size);  // Y = size
    axisVertices.push_back(0.0f);

    // Z-axis (Blue)
    axisVertices.push_back(0.0f);  // Start at the origin
    axisVertices.push_back(0.0f);
    axisVertices.push_back(0.0f);

    axisVertices.push_back(0.0f);  // End at (0, 0, size)
    axisVertices.push_back(0.0f);  // Z = size
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


    glLineWidth(5.0f);  // Set line width


    // Draw X-axis (Red)
    shader->setVec3("lineColor", glm::vec3(1.0f, 0.0f, 0.0f));  // Red
    glDrawArrays(GL_LINES, 0, 2);  // Draw the X-axis line

    // Draw Y-axis (Green)
    shader->setVec3("lineColor", glm::vec3(0.0f, 1.0f, 0.0f));  // Green
    glDrawArrays(GL_LINES, 2, 2);  // Draw the Y-axis line

    // Draw Z-axis (Blue)
    shader->setVec3("lineColor", glm::vec3(0.0f, 0.0f, 1.0f));  // Blue
    glDrawArrays(GL_LINES, 4, 2);  // Draw the Z-axis line

    // Cleanup
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}










// Enclosed function for drawing a cube (contains all rendering logic)
// ========================================================================

void DrawCube() {
    // Vertex data for a cube
    float vertices[] = {
        // positions         // colors
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,  // Back face
        4, 5, 6, 6, 7, 4,  // Front face
        0, 1, 5, 5, 4, 0,  // Bottom face
        3, 2, 6, 6, 7, 3,  // Top face
        0, 3, 7, 7, 4, 0,  // Left face
        1, 2, 6, 6, 5, 1   // Right face
    };

    // Vertex Shader
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out vec3 vertexColor;

        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            vertexColor = aColor;
        }
    )";

    // Fragment Shader
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 vertexColor;
        out vec4 FragColor;

        void main() {
            FragColor = vec4(vertexColor, 1.0);
        }
    )";

    static unsigned int VAO = 0, VBO = 0, EBO = 0, shaderProgram = 0;

    // Setup once
    if (VAO == 0) {
        // Generate and bind VAO, VBO, and EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // Vertex Buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Element Buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); // Position attribute

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1); // Color attribute

        glBindVertexArray(0);

        // Compile Vertex Shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        // Compile Fragment Shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Link Shaders into a Program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Clean up shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // Render
    glUseProgram(shaderProgram);

    // Set uniforms
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); // Rotate cube over time
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); // Move camera back
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void DrawCube2() {
    // Vertex data for a cube
    float vertices[] = {
        // positions         // colors
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,  // Back face
        4, 5, 6, 6, 7, 4,  // Front face
        0, 1, 5, 5, 4, 0,  // Bottom face
        3, 2, 6, 6, 7, 3,  // Top face
        0, 3, 7, 7, 4, 0,  // Left face
        1, 2, 6, 6, 5, 1   // Right face
    };

    // Vertex Shader
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out vec3 vertexColor;

        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            vertexColor = aColor;
        }
    )";

    // Fragment Shader
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 vertexColor;
        out vec4 FragColor;

        void main() {
            FragColor = vec4(vertexColor, 1.0);
        }
    )";

    static unsigned int VAO = 0, VBO = 0, EBO = 0, shaderProgram = 0;

    // Setup once
    if (VAO == 0) {
        // Generate and bind VAO, VBO, and EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // Vertex Buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Element Buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); // Position attribute

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1); // Color attribute

        glBindVertexArray(0);

        // Compile Vertex Shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        // Compile Fragment Shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Link Shaders into a Program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Clean up shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    // Render
    glUseProgram(shaderProgram);

    // Set uniforms
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); // Rotate cube over time
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); // Move camera back
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// ========================================================================
