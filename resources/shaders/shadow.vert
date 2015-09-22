#version 400 core
uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;
layout(location = 0) in vec3 in_Position;

void main() {
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(in_Position, 1.0);
}