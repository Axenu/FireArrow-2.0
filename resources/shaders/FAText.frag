#version 400 core

uniform sampler2D fontTexture;

in vec2 pass_UV;

out vec4 Frag_Data;

void main() {
    Frag_Data = vec4(1) * texture(fontTexture, pass_UV).r;
}