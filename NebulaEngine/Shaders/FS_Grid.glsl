#version 330 core


out vec4 FragColor;

uniform vec3 lineColor; // Color for the grid lines and X, Y, Z axis


void main() {
    FragColor = vec4(lineColor, 0.8f);
}