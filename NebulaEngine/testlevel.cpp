#define GLM_ENABLE_EXPERIMENTAL


#include "testlevel.h"
#include "helpers.h"
#include "gtx/string_cast.hpp"

void TestLevel::Start()
{
	std::cout << "TestLevel Start" << std::endl;

	// Initializations...
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

	defaultShader = new Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

	cube = createCube();
	cube->SetShader(defaultShader);

	

	

	

}



void TestLevel::Update(float deltaTime)
{
	// Level update logic...



	// std::cout << "TestLevel Update" << std::endl;

	//std::cout << glm::to_string(camera->GetViewMatrix()) << std::endl;





	// std::cout << camera->position.x << ", " << camera->position.y << ", " << camera->position.z << ", " << std::endl;
	/*std::cout << "model location: " << glGetUniformLocation(shader.ID, "Model") << std::endl;
	std::cout << "view location: " << glGetUniformLocation(shader.ID, "View") << std::endl;
	std::cout << "projection location: " << glGetUniformLocation(shader.ID, "Projection") << std::endl;*/



    //DrawCube();


	glm::mat4 Model = glm::mat4(1);
    
    cube->DrawWithShader(Model, camera->GetViewMatrix(), camera->GetProjectionMatrix());
    
}

void TestLevel::HandleInput(GLFWwindow* window, float deltaTime)
{
	// Camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->forward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(-camera->forward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(-camera->right, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->right, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->ProcessKeyboard(-camera->worldUp, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->worldUp, deltaTime);

	// Keyboard input handling...
}

void TestLevel::HandleMouseInput(GLFWwindow* window, double xpos, double ypos)
{
	// Mouse input handling...
}
