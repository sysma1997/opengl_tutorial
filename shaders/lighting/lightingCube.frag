#version 330 core

out vec4 frag;

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrengh = 0.1;
    vec3 ambient = ambientStrengh * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    frag = vec4(result, 1.0f);
}