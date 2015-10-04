#version 400 core

uniform sampler2D text;

in vec2 pass_UV;

out vec4 Frag_Data;

void main() {
    Frag_Data = texture(text, pass_UV);
    // Frag_Data = vec4(1);
}