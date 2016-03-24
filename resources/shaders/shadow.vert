#version 400 core
uniform mat4 MVPMatrix;
layout(location = 0) in vec3 in_Position;

void main() {
	gl_Position = MVPMatrix * vec4(in_Position, 1.0);
}