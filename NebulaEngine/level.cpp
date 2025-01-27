#include "level.h"
#include "helpers.h"

Level::Level()
{
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    gridShader = new Shader("Shaders/VS_Grid.glsl", "Shaders/FS_Grid.glsl");
}

Level::~Level() = default;

// Called once when the level/scene is initialized
void Level::Start() {
    // std::cout << "Level Start" << std::endl;

    
}

// Called once every frame to update level/scene logic
void Level::Update(float deltaTime) {
    // std::cout << "Level Update" << std::endl;

    if (displayGrid) {
        // Set the shader and view for the grid
        gridShader->use();

        glm::mat4 model = glm::mat4(1.0f); // No transformation for the grid
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = camera->GetProjectionMatrix();

        gridShader->setMat4("Model", model);
        gridShader->setMat4("View", view);
        gridShader->setMat4("Projection", projection);
        DrawGrid(50.0f, 1.0f, gridShader);  // Grid size of 50, step size of 1.0f
    }
}

// Handle keyboard input
void Level::HandleInput(GLFWwindow* window, float deltaTime) {
    // std::cout << "Handle Input" << std::endl;

    
    // Check if right mouse button is held down
    bool rightMousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;


    // Lock / unlock cursor
    if (rightMousePressed) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Lock cursor
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Unlock cursor
    }


    // Camera movement
    if (rightMousePressed)
    {
        // W - Forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->ProcessKeyboard(camera->forward, deltaTime);

        // S - Backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->ProcessKeyboard(-camera->forward, deltaTime);

        // A - Left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->ProcessKeyboard(-camera->right, deltaTime);

        // D - Right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->ProcessKeyboard(camera->right, deltaTime);

        // Q - Down
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera->ProcessKeyboard(-camera->worldUp, deltaTime);

        // E - Up
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera->ProcessKeyboard(camera->worldUp, deltaTime);
    }


    // Camera rotation
    static double lastX = 0.0f, lastY = 0.0f;
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    double xOffset = xPos - lastX;
    double yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    if (rightMousePressed) {
        camera->ProcessMouseMovement(xOffset, yOffset);
    }
}

// Handle mouse input
void Level::HandleMouseInput(GLFWwindow* window, double xpos, double ypos) {
    // std::cout << "Handle Mouse Input" << std::endl;
}
