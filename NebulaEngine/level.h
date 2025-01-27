#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "camera.h"
#include "shader.h"

class Level {
public:
    // Variables
    Camera* camera;
    bool displayGrid = true;
    Shader* gridShader;


    // Methods
    Level();
    virtual ~Level();

    // Called once when the level/scene is initialized
    virtual void Start();

    // Called once every frame to update level/scene logic
    virtual void Update(float deltaTime);

    // Handle keyboard input
    virtual void HandleInput(GLFWwindow* window, float deltaTime);

    // Handle mouse input
    virtual void HandleMouseInput(GLFWwindow* window, double xpos, double ypos);

    
};