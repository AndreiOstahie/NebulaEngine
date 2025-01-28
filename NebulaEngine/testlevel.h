#pragma once
#include "level.h"
#include "mesh.h"
#include "camera.h"
#include "shader.h"

class TestLevel : public Level {
private:
    Mesh* cube = nullptr;
    Shader* defaultShader;
    Shader* phongShader;
    Mesh suzanne;

    std::vector<PointLight> pointLights;

public:
    void Start() override;
    void Update(float deltaTime) override;
    void HandleInput(GLFWwindow* window, float deltaTime) override;
    void HandleMouseInput(GLFWwindow* window, double xpos, double ypos) override;
};