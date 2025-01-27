#define GLM_ENABLE_EXPERIMENTAL


#include "testlevel.h"
#include "helpers.h"
#include "gtx/string_cast.hpp"
#include "transform.h"

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

	/*cube->modelMatrix = Transform::RotateX(cube->modelMatrix, 30.0f);
	cube->modelMatrix = Transform::ScaleX(cube->modelMatrix, 5.0f);
	cube->modelMatrix = Transform::Scale(cube->modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
	cube->modelMatrix = Transform::Translate(cube->modelMatrix, glm::vec3(-0.5f, 0.0f, 0.0f));
	cube->modelMatrix = Transform::RotateY(cube->modelMatrix, 45.0f);*/
	
	
	cube->modelMatrix = Transform::RotateX(cube->modelMatrix, 45.0f);
	cube->modelMatrix = Transform::TranslateZ(cube->modelMatrix, -2.0f);
	cube->modelMatrix = Transform::ScaleUniform(cube->modelMatrix, 2.5f);

}




void TestLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);


	// Level update logic...


	
    cube->DrawWithShader(cube->modelMatrix, camera->GetViewMatrix(), camera->GetProjectionMatrix());
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
