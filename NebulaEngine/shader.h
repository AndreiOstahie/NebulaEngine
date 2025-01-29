#pragma once

#include <string>
#include "libs.h"



class Shader {
public:
    unsigned int ID;

    // Constructor that receives the file paths for vertex and fragment shaders
    Shader(const char* vertexPath, const char* fragmentPath);

    // Use the shader program
    void use();

    // Utility functions for setting uniform variables
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;

private:
    // Function that checks for any errors occuring during shader compilation
    void checkCompileErrors(unsigned int shader, std::string type);
};