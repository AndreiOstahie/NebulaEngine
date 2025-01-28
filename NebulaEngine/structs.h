#pragma once
#include <glm.hpp>
#include <string>

#define MAX_LIGHTS 10

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
	glm::vec3 color;
};

struct Texture {
	unsigned int id;	// OpenGL texture ID
	std::string type;	// Diffuse, specular etc.
	std::string path;	// Path to texture file
};

struct Material {
	glm::vec3 diffuse;	// Diffuse color
	glm::vec3 specular;	// Specular color
	float shininess;	// Shininess factor for specular color
};


// Point light properties
struct PointLight {
	glm::vec3 position;  // Position of the light
	glm::vec3 color;     // Color of the light
	float strength; // Light intensity
};