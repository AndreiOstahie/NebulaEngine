// NebulaEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// Window size
const GLint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;




int main()
{
    std::cout << "Hello World!\n";



    // Init GLFW and return error for failure
    if (!glfwInit())
    {
        cout << "ERROR: Failed to initialize GLFW" << endl;
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // Set OpenGL version (OpenGL 3.3)
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


    // Loop until window is closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Handle user input events
        glfwPollEvents();

        // Clear Window (color data)
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap between the 2 buffers
        glfwSwapBuffers(mainWindow);
    }


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
