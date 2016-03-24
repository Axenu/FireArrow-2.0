#version 400 core

layout(location = 0) in vec3 in_Position;

out vec2 pass_UV;

void main() {
	pass_UV = vec2(in_Position.x, in_Position.y + 1);
	gl_Position = vec4(in_Position.x * 2 - 1, in_Position.y * 2 + 1, in_Position.z, 1);

}