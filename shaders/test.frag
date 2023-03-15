#version 330 core

out vec3 color;

/* in vec3 fragmentColor; */
in vec2 UV;

uniform sampler2D myTextureSampler;

void main() {
    color = texture(myTextureSampler, UV).rgb;
}