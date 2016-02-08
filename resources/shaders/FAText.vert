#version 400 core

uniform vec2 position;
// uniform vec2 size;

layout(location = 0) in vec2 in_Position;
layout(location = 1) in vec2 in_UV;

out vec2 pass_UV;

void main() {
	pass_UV = in_UV;
    gl_Position = vec4(in_Position + position*2, 0,1);
}