#version 330 core

out vec4 frag;

in vec2 textCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    frag = mix(texture(texture1, textCoord), texture(texture2, textCoord), 0.2f);
}