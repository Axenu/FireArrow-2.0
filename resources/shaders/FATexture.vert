#version 400 core

uniform vec2 position;
uniform vec2 size;

layout(location = 0) in vec3 in_Position;

out vec2 pass_UV;

void main() {
	pass_UV = vec2(in_Position.xy);
    gl_Position = vec4(in_Position.xy * size + position, 0, 1.0);
}