#version 330 core
out vec4 FragColor;

uniform vec3 lineColor; // Color for the lines

void main() {
    FragColor = vec4(lineColor, 0.8f);

}