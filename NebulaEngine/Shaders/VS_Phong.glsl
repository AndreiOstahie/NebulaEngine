#version 330 core

// Input
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;

// Uniforms
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output to fragment shader
out vec3 FragPos;   // Position in world space
out vec3 NormalDir; // Normal in world space

void main()
{
    FragPos = vec3(Model * vec4(Position, 1.0));  // Transform vertex position to world space
    NormalDir = mat3(transpose(inverse(Model))) * Normal;  // Transform normal to world space
    // NormalDir = normalize( mat3(Model) * Normal);  // Transform normal to world space

    gl_Position = Projection * View * vec4(FragPos, 1.0);
}
