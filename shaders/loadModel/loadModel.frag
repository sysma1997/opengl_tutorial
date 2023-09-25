#version 330 core

out vec4 frag;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 color;

void main() {
    frag = texture(texture_diffuse1, texCoords);
    /* frag = vec4(color, 1.0); */
}