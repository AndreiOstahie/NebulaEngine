#define GLM_ENABLE_EXPERIMENTAL


#include "testlevel.h"
#include "helpers.h"
#include "gtx/string_cast.hpp"
#include "transform.h"
#include "mesh_loader.h"

void TestLevel::Start()
{
	Level::Start();


	std::cout << "TestLevel Start" << std::endl;

	// Initializations...
	camera = new Camera(glm::vec3(0.0f, 5.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -75.0f, -15.0f);
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

	MeshLoader loader;
	suzanne = loader.LoadMesh("Resources/Meshes/SuzanneObj.obj", false);
	suzanne.modelMatrix = Transform::TranslateX(suzanne.modelMatrix, 5.0f);

	phongShader = new Shader("Shaders/VS_Phong.glsl", "Shaders/FS_Phong.glsl");
	suzanne.SetShader(phongShader);
	suzanne.material.diffuse = glm::vec3(1.0f, 1.0f, 0.0f);
	suzanne.material.specular = glm::vec3(1.0f, 1.0f, 0.0f);
	suzanne.material.shininess = 30.0f;

	pointLights = {
	{{5.0f, 7.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 1.0f}, // White light
	//{{-5.0f, 5.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 0.8f} // Red light
	};
}




void TestLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);


	// Level update logic...

	suzanne.modelMatrix = Transform::RotateY(suzanne.modelMatrix, deltaTime * 30.0f);
	suzanne.DrawWithPhongShader(suzanne.modelMatrix, camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->position, pointLights);


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
