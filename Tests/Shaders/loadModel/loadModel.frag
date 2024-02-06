#version 330 core

out vec4 frag;

in vec2 texCords;

uniform sampler2D texture_diffuse1;

void main() {
    frag = texture(texture_diffuse1, texCords);
}