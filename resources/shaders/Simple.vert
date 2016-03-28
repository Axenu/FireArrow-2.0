#version 400 core 

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec3 in_Color;

out vertexData {
	vec4 pass_Position;
	vec4 pass_Normal;
	vec4 pass_Color;
} VertexOut;


uniform mat4 MVPMatrix;
uniform mat4 ModelMatrix;
uniform mat4 NormalMatrix;

void main() {
	VertexOut.pass_Position = ModelMatrix * vec4(in_Position.xyz, 1.0);
	VertexOut.pass_Normal = NormalMatrix * vec4(in_Normal, 1.0);
	VertexOut.pass_Color = vec4(in_Color, 1.0);
	gl_Position = MVPMatrix * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
}