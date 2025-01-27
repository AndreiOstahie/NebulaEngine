#include "level.h"


Level::~Level() = default;

// Called once when the level/scene is initialized
void Level::Start() {
    std::cout << "Level Start" << std::endl;
}

// Called once every frame to update level/scene logic
void Level::Update(float deltaTime) {
    std::cout << "Level Update" << std::endl;
}

// Handle keyboard input
void Level::HandleInput(GLFWwindow* window, float deltaTime) {
    std::cout << "Handle Input" << std::endl;
}

// Handle mouse input
void Level::HandleMouseInput(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "Handle Mouse Input" << std::endl;
}
