#version 330 core

// Input
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;
layout (location = 3) in vec3 VColor;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 vertexColor;

void main() {

    gl_Position = Projection * View * Model * vec4(Position, 1.0f);
    vertexColor = VColor;
}