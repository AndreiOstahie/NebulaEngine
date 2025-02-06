#define GLM_ENABLE_EXPERIMENTAL


#include "testlevel.h"
#include "helpers.h"
#include "gtx/string_cast.hpp"
#include "transform.h"
#include "mesh_loader.h"


// Function that rotates the moving point lights in the scene around a given position (center)
void UpdatePointLights(std::vector<PointLight>& pointLights, float deltaTime, glm::vec3 center, float rotationSpeed) {
	// Rotation angle in radians
	static float angle = 0.0f;
	angle += rotationSpeed * deltaTime;

	// Distance from the center to the lights
	float radius = 3.5f;

	for (int i = 0; i < pointLights.size(); i++) {
		// Place the point lights around the center, in a circle (360 degrees / number of lights)
		float lightAngle = angle + glm::radians(360.0f / pointLights.size() * i);

		// Calculate the new position of the point light
		pointLights[i].position = center + glm::vec3(radius * cos(lightAngle), 0.0f, radius * sin(lightAngle));
	}
}


void TestLevel::Start()
{
	// Call parent class "Start" implementation
	Level::Start();
	
	// Create camera with initial position and rotation
	camera = new Camera(glm::vec3(0.0f, 5.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -75.0f, -15.0f);

	// Enable/disable grid
	displayGrid = true;

	// Create shaders
	defaultShader = new Shader("../Shaders/VertexShader.glsl", "../Shaders/FragmentShader.glsl");
	baseColorShader = new Shader("../Shaders/VS_BaseColor.glsl", "../Shaders/FS_BaseColor.glsl");
	vertexColorShader = new Shader("../Shaders/VS_VertexColor.glsl", "../Shaders/FS_VertexColor.glsl");
	phongShader = new Shader("../Shaders/VS_Phong.glsl", "../Shaders/FS_Phong.glsl");

	// Create mesh loader
	MeshLoader loader;

	// Create/load meshes
	cube = createCube();
	vertexColorsCube = createCube();
	suzanne = loader.LoadMesh("../Resources/Meshes/SuzanneObj.obj", false);
	suzanne2 = loader.LoadMesh("../Resources/Meshes/SuzanneObj.obj", false);
	pointLightMesh = loader.LoadMesh("../Resources/Meshes/sphere.obj", false);
	
	// Set mesh shaders
	cube->SetShader(defaultShader);
	vertexColorsCube->SetShader(vertexColorShader);
	suzanne.SetShader(phongShader);
	suzanne2.SetShader(phongShader);

	// Apply initial transformations to the meshes
	cube->modelMatrix = Transform::RotateX(cube->modelMatrix, 45.0f);
	cube->modelMatrix = Transform::TranslateZ(cube->modelMatrix, -2.0f);
	cube->modelMatrix = Transform::ScaleUniform(cube->modelMatrix, 2.5f);
	suzanne.modelMatrix = Transform::TranslateX(suzanne.modelMatrix, 5.0f);
	
	// Set mesh material properties
	suzanne.material.diffuse = glm::vec3(1.0f, 1.0f, 0.0f);
	suzanne.material.specular = glm::vec3(1.0f, 1.0f, 0.0f);
	suzanne.material.shininess = 30.0f;
	suzanne2.material.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	suzanne2.material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	suzanne2.material.shininess = 50.0f;
	
	
	// Initialize point lights
	pointLightMeshScale = glm::vec3(0.1f, 0.1f, 0.1f);  // point light preview mesh scale
	controllablePointLightPosition = glm::vec3(5.0f, 5.0f, 0.0f);  // controllable point light starting position
	controllablePointLightColor = glm::vec3(1.0f, 1.0f, 1.0f);  // controllable point light color
	controllablePointLight = {{controllablePointLightPosition, controllablePointLightColor, 1.0f}}; // An array with a single point light because of the way the shader receives data about point lights
	pointLightMesh.SetShader(baseColorShader);  // use a base color shader for the point light mesh
	
	// Create the moving point lights, with random colors 
	srand(2);
	movingPointLights = {
	{glm::vec3(-9.0f, 3.0f, 0), glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f), 1.0f},
	{glm::vec3(-5.0f, 3.0f, 0), glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f), 1.0f},
	{glm::vec3(-7.0f, 3.0f, -2.0f), glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f), 1.0f},
	{glm::vec3(-7.0f, 3.0f, 2.0f), glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f), 1.0f},
	};

	pointLightsRotationSpeed = glm::radians(45.0f);
	center = glm::vec3(-7.0f, 3.0f, 0.0f);
}




void TestLevel::Update(float deltaTime)
{
	// Call parent class "Update" implementation
	Level::Update(deltaTime);


	// Draw a test cube mesh
	cube->DrawWithShader(cube->modelMatrix, camera->GetViewMatrix(), camera->GetProjectionMatrix());


	// Draw rotating Suzanne mesh that uses the Phong shading model,
	// reacting to a single light source (the controllable one)
	suzanne.modelMatrix = Transform::RotateY(suzanne.modelMatrix, deltaTime * 30.0f);
	suzanne.DrawWithPhongShader(suzanne.modelMatrix, camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->position, controllablePointLight);


	// Draw controllable point light mesh
	glm::mat4 model = glm::mat4(1);
	model = Transform::Translate(model, controllablePointLight[0].position);
	model = Transform::Scale(model, pointLightMeshScale);
	pointLightMesh.DrawWithShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix(), controllablePointLightColor);


	// Draw another Suzanne mesh that uses the Phong shading model,
	// reacting to the multiple moving point lights
	model = glm::mat4(1);
	model = Transform::Translate(model, center);
	suzanne2.DrawWithPhongShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix(), camera->position, movingPointLights);


	// Update and draw moving point lights
	UpdatePointLights(movingPointLights, deltaTime, center, pointLightsRotationSpeed);
	
	for (int i = 0; i < movingPointLights.size(); i++)
	{
		model = glm::mat4(1);
		model = Transform::Translate(model, movingPointLights[i].position);
		model = Transform::Scale(model, pointLightMeshScale);

		pointLightMesh.DrawWithShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix(), movingPointLights[i].color);
	}


	// Update and render the moving cube
	{
		if (currentTranslation <= minTranslation) {
			translatePositive = true;
		}
		else if (currentTranslation >= maxTranslation) {
			translatePositive = false;
		}

		if (translatePositive) {
			currentTranslation += deltaTime * translationSpeed;
		}
		else {
			currentTranslation -= deltaTime * translationSpeed;
		}

		model = glm::mat4(1);
		model = Transform::Translate(model, glm::vec3(-5.0f, 7.0f, 0.0f));
		model = Transform::TranslateX(model, currentTranslation);
		model = Transform::TranslateZ(model, currentTranslation);

		vertexColorsCube->DrawWithShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}


	//  Update and render the scaling cube
	{
		if (currentScale <= minScale) {
			scaleUp = true;
		}
		else if (currentScale >= maxScale) {
			scaleUp = false;
		}

		if (scaleUp) {
			currentScale += deltaTime * scalingSpeed;
		}
		else {
			currentScale -= deltaTime * scalingSpeed;
		}

		model = glm::mat4(1);
		model = Transform::Translate(model, glm::vec3(0.0f, 7.0f, 0.0f));
		model = Transform::ScaleUniform(model, currentScale);

		vertexColorsCube->DrawWithShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}


	//  Update and render the rotating cube
	{
		currentRotation += deltaTime * rotationSpeed;

		model = glm::mat4(1);
		model = Transform::Translate(model, glm::vec3(5.0f, 7.0f, 0.0f));
		model = Transform::RotateX(model, currentRotation);
		model = Transform::RotateY(model, currentRotation);

		vertexColorsCube->DrawWithShader(model, camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}
}


void TestLevel::HandleInput(GLFWwindow* window, float deltaTime)
{
	// Call parent class "HandleInput" implementation
	Level::HandleInput(window, deltaTime);


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
