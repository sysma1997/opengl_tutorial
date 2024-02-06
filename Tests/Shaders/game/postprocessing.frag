#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D scene;
uniform vec2 offsets[9];
uniform int edgeKernel[9];
uniform float blurKernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main() {
    color = vec4(0.0);
    vec3 sample[9];

    if(chaos || shake)
        for(int i = 0; i < 9; i++) sample[i] = vec3(texture(scene, texCoords.st + offsets[i]));

    if(chaos) {
        for(int i = 0; i < 9; i++) color += vec4(sample[i] * edgeKernel[i], 0.0);
        color.a = 1.0;
    } else if(confuse) {
        color = vec4(1.0 - texture(scene, texCoords).rgb, 1.0);
    } else if(shake) {
        for(int i = 0; i < 9; i++) color += vec4(sample[i] * blurKernel[i], 0.0);
        color.a = 1.0;
    } else
        color = texture(scene, texCoords);
}