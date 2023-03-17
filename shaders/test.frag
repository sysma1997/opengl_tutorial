#version 330 core

in vec2 UV;

//out vec3 color;
out vec4 fragColor;

uniform sampler2D myTextureSampler;

void main() {
    //color = texture(myTextureSampler, UV).rgb;
    fragColor = texture(myTextureSampler, UV);
}