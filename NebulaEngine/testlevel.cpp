#define GLM_ENABLE_EXPERIMENTAL


#include "testlevel.h"
#include "helpers.h"
#include "gtx/string_cast.hpp"

void TestLevel::Start()
{
	Level::Start();


	std::cout << "TestLevel Start" << std::endl;

	// Initializations...
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	displayGrid = true;

	defaultShader = new Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

	cube = createCube();
	cube->SetShader(defaultShader);

	

	

	

}




void TestLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);


	// Level update logic...


	glm::mat4 Model = glm::mat4(1);
    
    cube->DrawWithShader(Model, camera->GetViewMatrix(), camera->GetProjectionMatrix());
}

void TestLevel::HandleInput(GLFWwindow* window, float deltaTime)
{
	Level::HandleInput(window, deltaTime);
	// Keyboard input handling...
}

void TestLevel::HandleMouseInput(GLFWwindow* window, double xpos, double ypos)
{
	// Mouse input handling...
}
