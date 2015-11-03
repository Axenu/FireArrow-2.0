#version 400 core

uniform vec4 color;

out vec4 Frag_Data;

void main() {
    Frag_Data = color;
}