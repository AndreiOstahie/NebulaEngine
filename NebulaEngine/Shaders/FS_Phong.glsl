#version 330 core

out vec4 FragColor;

// Input from vertex shader
in vec3 FragPos;
in vec3 NormalDir;


// Uniforms for material properties
uniform vec3 materialDiffuse;  // Diffuse color
uniform vec3 materialSpecular; // Specular color
uniform float materialShininess; // Shininess factor


uniform vec3 viewPos;  // Camera/eye position


// Point light properties
struct PointLight {
    vec3 position;  // Light position
    vec3 color;     // Light color
    float strength; // Light intensity
};


// Uniforms for point lights
#define MAX_LIGHTS 10
uniform PointLight pointLights[MAX_LIGHTS]; // Array of point lights
uniform int numLights; // Number of active lights



// Compute the ambient light component
vec3 ComputeAmbientComponent()
{
    vec3 global_ambient_color = vec3(0.25f);
    vec3 ambient_component = 0.2f * global_ambient_color;

    return ambient_component;
}


// Compute the light attenuation factor based on the distance
// between the position of the light source and the position of the illuminated point
float ComputeDistanceAttenuation(vec3 light_position, vec3 point_position)
{
    // Get distance between the light source and the point
    float d = distance(light_position, point_position);

    
    // Compute attenuation based on distance and falloff constants
    float falloffConstant_1 = 0.5f;
    float falloffConstant_2 = 0.1f;
    float attenuation = 1.0 / (1.0 + falloffConstant_1 * d + falloffConstant_2 * d * d);
    
    return attenuation;

    // return 1 / (pow(d, 2) + 1);
}


// Compute Phong illumination (diffuse, specular)
vec3 ComputePhongIllumination(vec3 light_position)
{
    // Compute the diffuse component
    vec3 L = normalize(light_position - FragPos);  // vector between fragment and light source
    vec3 diffuse_component =  materialDiffuse * max(dot(normalize(NormalDir), L), 0);

    
    // Check if fragment receives light
    int receivesLight = 0;
    if (dot(NormalDir, L) > 0)
    {
        receivesLight = 1;
    }

    vec3 R = reflect (-L, normalize(NormalDir));  // light reflection vector
    vec3 viewDir = normalize(viewPos - FragPos);  // vector between fragment and camera

    // Compute the specular component
    vec3 specular_component = vec3(0);
    specular_component = materialSpecular * receivesLight * pow(max(dot(viewDir, R), 0), materialShininess);

    // Compute the final illumination (diffuse + specular)
    vec3 illumination = diffuse_component + specular_component;

    return illumination;
}


// Compute lighting from the point light sources
vec3 ComputePointLightSourcesIllumination()
{
    vec3 lights_illumination = vec3(0);

    // Compute Phong illumination and light attenuation for each light source
    for (int i=0;i<numLights;i++) {
        vec3 light_position = pointLights[i].position;
        vec3 light_color = pointLights[i].color;

        vec3 light_illumination = ComputePhongIllumination(light_position);
        float illumination_attenuation = ComputeDistanceAttenuation(light_position, FragPos);

        // Add the illumination from the current light source to the result
        lights_illumination += vec3(pointLights[i].strength) * light_illumination * illumination_attenuation * light_color;
    }

    return lights_illumination;
}



void main()
{
    // Add the light components to get the final color value
    vec3 illumination = ComputePointLightSourcesIllumination() + ComputeAmbientComponent();

    FragColor = vec4 (illumination, 1);
}
