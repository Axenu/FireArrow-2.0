#version 400 core 

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Offset;

out vec3 pass_Offset;

void main() {
	gl_Position = vec4(in_Position * 0.1, 1.0);
	//pass in_offset
	pass_Offset = in_Offset;
}