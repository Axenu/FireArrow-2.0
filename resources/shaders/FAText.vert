#version 400 core

uniform vec3 position;
uniform vec2 size;

layout(location = 0) in vec3 in_Position;

out vec2 pass_UV;

void main() {
	pass_UV = vec2(in_Position.x, in_Position.y);
    gl_Position = vec4((position.x + size.x * in_Position.x) - 1, (-position.y - size.y * in_Position.y) - 1, position.z, 1.0);
}