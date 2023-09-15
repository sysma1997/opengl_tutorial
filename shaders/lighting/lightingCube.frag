#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float contant;
    float linear;
    float quadratic;
};

out vec4 frag;

in vec3 normal;
in vec3 fragPos;
in vec2 texCord;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.contant + light.linear * distance + light.quadratic * (distance * distance));

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCord));
    ambient *= attenuation;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCord));
    diffuse *= attenuation;

    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCord));
    specular *= attenuation;

    frag = vec4(ambient + diffuse + specular, 1.0);
}