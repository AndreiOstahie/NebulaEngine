#version 330 core


in vec3 vertexColor;

out vec4 FragColor;


void main() {
    // Calculate the fragment color by interpolating between vertex colors
    FragColor = vec4(vertexColor, 1.0f);
}