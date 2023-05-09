#version 330 core

out vec4 frag;

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 viewPos;
float specularStrength = 0.5f;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrengh = 0.1;
    vec3 ambient = ambientStrengh * lightColor;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spect = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
    vec3 specular = specularStrength * spect * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    frag = vec4(result, 1.0f);
}