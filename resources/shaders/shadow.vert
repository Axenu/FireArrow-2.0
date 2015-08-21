#version 150 core

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

in vec3 in_Position;

void main() {
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(in_Position, 1.0);
}