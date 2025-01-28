#define GLM_ENABLE_EXPERIMENTAL


#include "testlevel.h"
#include "helpers.h"
#include "gtx/string_cast.hpp"
#include "transform.h"
#include "mesh_loader.h"


void UpdatePointLights(std::vector<PointLight>& pointLights, float deltaTime, glm::vec3 center, float rotationSpeed) {
	static float angle = 0.0f; // Angle of rotation in radians
	angle += rotationSpeed * deltaTime;

	float radius = 3.5f; // Distance from the center to the lights

	for (int i = 0; i < pointLights.size(); i++) {
		// Evenly space the lights in a circle (divide 360 degrees by the number of lights)
		float lightAngle = angle + glm::radians(360.0f / pointLights.size() * i);

		// Compute the new position of the light
		pointLights[i].position = center + glm::vec3(
			radius * cos(lightAngle),  // X
			0.0f,                     // Y (height stays constant)
			radius * sin(lightAngle)  // Z
		);
	}
}


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

	pointLightMeshScale = glm::vec3(0.1f, 0.1f, 0.1f);

	controllablePointLightPosition = glm::vec3(5.0f, 5.0f, 0.0f);
	controllablePointLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	
	controllablePointLight = {
	{controllablePointLightPosition, controllablePointLightColor, 1.0f}, // White light
	};

	pointLightMesh = loader.LoadMesh("Resources/Meshes/sphere.obj", false);
	
	baseColorShader = new Shader("Shaders/VS_BaseColor.glsl", "Shaders/FS_BaseColor.glsl");
	pointLightMesh.SetShader(baseColorShader);

	srand(2);
	movingPointLights = {
	{glm::vec3(-9.0f, 3.0f, 0), glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f), 1.0f},
	{glm::vec3(-5.0f, 3.0f, 0), glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f), 1.0f},
	{glm::vec3(-7.0f, 3.0f, -2.0f), glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f), 1.0f},
	{glm::vec3(-7.0f, 3.0f, 2.0f), glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f), 1.0f},
	};

	for (int i = 0; i < movingPointLights.size(); i++) {
		movingPointLightsModelMatrices.push_back(glm::mat4(1));
	}

	suzanne2 = loader.LoadMesh("Resources/Meshes/SuzanneObj.obj", false);
	suzanne2.SetShader(phongShader);
	suzanne2.material.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	suzanne2.material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	suzanne2.material.shininess = 50.0f;
}




void TestLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);

	// Level update logic...

	// Draw test cube
	cube->DrawWithShader(cube->modelMatrix, camera->GetViewMatrix(), camera->GetProjectionMatrix());


	// Draw rotating Suzanne
	suzanne.modelMatrix = Transform::RotateY(suzanne.modelMatrix, deltaTime * 30.0f);
	suzanne.DrawWithPhongShader(suzanne.modelMatrix, camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->position, controllablePointLight);


	// Draw controllable point light mesh
	glm::mat4 model = glm::mat4(1);
	model = Transform::Translate(model, controllablePointLight[0].position);
	model = Transform::Scale(model, pointLightMeshScale);
	pointLightMesh.DrawWithShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix(), controllablePointLightColor);


	// Draw another Suzanne
	model = glm::mat4(1);
	model = Transform::Translate(model, glm::vec3(-7.0f, 3.0f, 0.0f));
	suzanne2.DrawWithPhongShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->position, movingPointLights);


	// Update and draw moving point lights
	float rotationSpeed = glm::radians(45.0f); // 45 degrees per second
	glm::vec3 center = glm::vec3(-7.0f, 3.0f, 0.0f); // Object's position

	UpdatePointLights(movingPointLights, deltaTime, center, rotationSpeed);
	
	for (int i = 0; i < movingPointLights.size(); i++)
	{
		model = glm::mat4(1);
		model = Transform::Translate(model, movingPointLights[i].position);
		model = Transform::ScaleUniform(model, 0.1f);
		

		pointLightMesh.DrawWithShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix(), movingPointLights[i].color);
	}
}

void TestLevel::HandleInput(GLFWwindow* window, float deltaTime)
{
	Level::HandleInput(window, deltaTime);
	// Keyboard input handling...


	// Check if right mouse button is held down
	bool rightMousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

	// Controllable point light movement
	if (!rightMousePressed)
	{
		// W - Forward
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			controllablePointLight[0].position.z -= controllablePointLightSpeed * deltaTime;

		// S - Backward
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			controllablePointLight[0].position.z += controllablePointLightSpeed * deltaTime;

		// A - Left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			controllablePointLight[0].position.x -= controllablePointLightSpeed * deltaTime;

		// D - Right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			controllablePointLight[0].position.x += controllablePointLightSpeed * deltaTime;

		// Q - Down
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			controllablePointLight[0].position.y -= controllablePointLightSpeed * deltaTime;

		// E - Up
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			controllablePointLight[0].position.y += controllablePointLightSpeed * deltaTime;
	}
}

void TestLevel::HandleMouseInput(GLFWwindow* window, double xpos, double ypos)
{
	// Mouse input handling...
}
