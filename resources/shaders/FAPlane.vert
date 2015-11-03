#version 400 core

uniform vec2 position;
uniform vec2 size;

layout(location = 0) in vec3 in_Position;

void main() {
    gl_Position = vec4(in_Position.xy * size + position, 0, 1.0);
}