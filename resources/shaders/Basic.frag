#version 400 core

// in vec4 pass_Normal;
// in vec4 pass_Color;

out vec4 Frag_Data;

uniform vec4 ucolor;

void main() {
    // Frag_Data = pass_Color;
    Frag_Data = ucolor;
}