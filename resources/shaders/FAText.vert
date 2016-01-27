#version 400 core

uniform vec3 position;
uniform vec2 size;

layout(location = 0) in vec3 in_Position;
layout(location = 3) in vec2 in_UV;

out vec2 pass_UV;

void main() {
	pass_UV = in_UV;
    gl_Position = vec4((in_Position.x * size.x + position.x), (in_Position.y * size.y + position.y), position.z, 1.0);
}