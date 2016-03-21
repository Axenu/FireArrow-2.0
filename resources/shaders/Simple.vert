#version 400 core 

layout(location = 0) in vec3 in_Position;
layout(location = 2) in vec3 in_Color;

out vec4 pass_Color;

uniform mat4 MVPMatrix;

void main() {
	pass_Color = vec4(in_Color, 1.0);
	gl_Position = MVPMatrix * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
}