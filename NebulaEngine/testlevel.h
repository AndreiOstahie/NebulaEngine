#pragma once
#include "level.h"
#include "mesh.h"


class TestLevel : public Level {
private:
    Mesh* cube = nullptr;

public:
    void Start() override;
    void Update(float deltaTime) override;
    void HandleInput(GLFWwindow* window) override;
    void HandleMouseInput(GLFWwindow* window, double xpos, double ypos) override;
};