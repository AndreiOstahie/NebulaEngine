// NebulaEngine.cpp : Contains the 'main' function.


#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "libs.h"
#include "testlevel.h"
#include "helpers.h"

using namespace std;


// Application window size
const GLint WINDOW_WIDTH = 1024, WINDOW_HEIGHT = 720;



int main()
{
    // Init GLFW and return error for failure
    if (!glfwInit())
    {
        cout << "ERROR: Failed to initialize GLFW" << endl;
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // Set OpenGL version (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // disable backward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // enable forward compatibility


    // Create GLFW window
    GLFWwindow* mainWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Nebula Engine", NULL, NULL);

    // Check window creation result
    if (!mainWindow)
    {
        cout << "ERROR: Failed to create GLFW window" << endl;
        glfwTerminate();
        return 1;
    }

    // Get buffer size
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set GLEW context
    glfwMakeContextCurrent(mainWindow);

    // Enable GLEW modern extension features
    glewExperimental = GL_TRUE;

    // Init GLEW and check for result
    if (glewInit() != GLEW_OK)
    {
        cout << "ERROR: Failed to initialize GLEW" << endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Set viewport
    glViewport(0, 0, bufferWidth, bufferHeight);


    // Enable depth testing
    glEnable(GL_DEPTH_TEST);


    // Create a level
    Level* level = new TestLevel();

    // Call the level's Start function for initializations
    level->Start();

    // Engine frame time
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    

    // Loop until window is closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Calculate deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Process user input events
        glfwPollEvents();

        // Clear Window (color data and depth data)
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handle user input (logic is implemented in Level class or other classes that inherit the base Level class)
        level->HandleInput(mainWindow, deltaTime);

        // Update the current level
        level->Update(deltaTime);

        // Swap between the 2 buffers
        glfwSwapBuffers(mainWindow);
    }

    // Cleanup
    delete level;
    level = nullptr;
    glfwDestroyWindow(mainWindow);
    glfwTerminate();


    return 0;
}