#version 330 core

out vec4 FragColor;

// Input from vertex shader
in vec3 FragPos;
in vec3 NormalDir;


// Uniforms for material properties
uniform vec3 materialDiffuse;  // Material diffuse color
uniform vec3 materialSpecular; // Material specular color
uniform float materialShininess; // Material shininess factor

uniform vec3 viewPos;

// Point light properties
struct PointLight {
    vec3 position;  // Position of the light
    vec3 color;     // Color of the light
    float strength; // Light intensity
};


// Uniforms for point lights
#define MAX_LIGHTS 8
uniform PointLight pointLights[MAX_LIGHTS]; // Array of point lights
uniform int numLights; // Number of active lights




vec3 ComputeAmbientComponent()
{
    vec3 global_ambient_color = vec3(0.25f);
    vec3 ambient_component = 0.2f * global_ambient_color;

    return ambient_component;
}


float ComputeDistanceAttenuation(vec3 light_position, vec3 point_position)
{
    // Compute the light attenuation factor based on the distance
    // between the position of the illuminated point and the position of the light source.
    float d = distance(light_position, point_position);

    // return 1 / (pow(d, 2) + 1);

    float falloffConstant_1 = 0.5f;
    float falloffConstant_2 = 0.f;
    float attenuation = 1.0 / (1.0 + falloffConstant_1 * d + falloffConstant_2 * d * d);
    
    return attenuation;
}


vec3 ComputePhongIllumination(vec3 light_position)
{
    // Compute the diffuse component of the Lambert illumination model
    vec3 L = normalize(light_position - FragPos);
    vec3 diffuse_component =  materialDiffuse * max(dot(normalize(NormalDir), L), 0);

    // Compute the specular component of the Phong illumination model
    int receivesLight = 0;
    if (dot(NormalDir, L) > 0)
    {
        receivesLight = 1;
    }
    vec3 R = reflect (-L, normalize(NormalDir));

    vec3 specular_component = vec3(0);

    // if (length(diffuse_component) > 0)
    // {
      // receivesLight = 1;
    // }

    vec3 viewDir = normalize(viewPos - FragPos);
    specular_component = materialSpecular * receivesLight * pow(max(dot(viewDir, R), 0), materialShininess);

    // Compute the final illumination as the sum of the diffuse and specular components
    vec3 illumination = diffuse_component + specular_component;

    return illumination;
}


vec3 ComputePointLightSourcesIllumination()
{
    vec3 lights_illumination = vec3(0);

    for (int i=0;i<numLights;i++) {
        vec3 light_position = pointLights[i].position;
        vec3 light_color = pointLights[i].color;

        vec3 light_illumination = ComputePhongIllumination(light_position);
        float illumination_attenuation = ComputeDistanceAttenuation(light_position, FragPos);

        // Add to the illumination of all light sources the result
        // of multiplying the illumination of the light source from the current iteration
        // with the attenuation of the illumination and the color of the illumination.
        lights_illumination += vec3(pointLights[i].strength) * light_illumination * illumination_attenuation * light_color;
    }

    return lights_illumination;
}



void main()
{
    vec3 illumination = ComputePointLightSourcesIllumination()
        + ComputeAmbientComponent();

    FragColor = vec4 (illumination, 1);
}










/*
out vec4 FragColor;

// Input from vertex shader
in vec3 FragPos;
in vec3 NormalDir;

// Uniforms for material properties
uniform vec3 materialDiffuse;  // Material diffuse color
uniform vec3 materialSpecular; // Material specular color
uniform float materialShininess; // Material shininess factor


// Point light properties
struct PointLight {
    vec3 position;  // Position of the light
    vec3 color;     // Color of the light
    float strength; // Light intensity
};


// Uniforms for point lights
#define MAX_LIGHTS 8
uniform PointLight pointLights[MAX_LIGHTS]; // Array of point lights
uniform int numLights; // Number of active lights


// Function to calculate lighting for a single point light
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos)
{
    // Calculate light direction
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color * materialDiffuse;

    // Specular shading
    vec3 viewDir = normalize(-fragPos); // Assume the camera is at the origin
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = spec * light.color * materialSpecular;

    // Combine and scale by light strength
    return (diffuse + specular) * light.strength;
}


void main()
{
    // Normalize the normal direction
    vec3 normal = normalize(NormalDir);

    // Sum contributions from all active lights
    vec3 result = vec3(0.0);
    for (int i = 0; i < numLights; i++) {
        result += CalculatePointLight(pointLights[i], normal, FragPos);
    }

    // Output the final color
    FragColor = vec4(result, 1.0);




    //FragColor = vec4(materialDiffuse, 1.0);
}
*/