#include "testlevel.h"
#include "helpers.h"

void TestLevel::Start()
{
	std::cout << "TestLevel Start" << std::endl;
	cube = createCube();

	// Initializations...
}

void TestLevel::Update(float deltaTime)
{
	std::cout << "TestLevel Update" << std::endl;
	cube->Draw();

	// Scene logic...
}

void TestLevel::HandleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		std::cout << "W Key Pressed" << std::endl;
	}

	// Keyboard input handling...
}

void TestLevel::HandleMouseInput(GLFWwindow* window, double xpos, double ypos)
{
	// Mouse input handling...
}
