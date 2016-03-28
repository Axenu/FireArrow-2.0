#version 400 core

layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;
 
in vertexData {
	vec4 pass_Position;
	vec4 pass_Normal;
	vec4 pass_Color;
} VertexIn[];
 
out vertexData {
	vec4 pass_Position;
	vec4 pass_Normal;
	vec4 pass_Color;
} VertexOut;

uniform mat4 ModelMatrix;
uniform vec3 cameraPosition;
 
 void main() {
 	vec3 vt = normalize(VertexIn[0].pass_Position.xyz - cameraPosition);
	if (dot(-VertexIn[0].pass_Normal.xyz, vt) > 0) {
		for(int i = 0; i < 3; i++) {
		    gl_Position = gl_in[i].gl_Position;
		    VertexOut.pass_Position = VertexIn[i].pass_Position;
		    VertexOut.pass_Normal = VertexIn[i].pass_Normal;
		    VertexOut.pass_Color = VertexIn[i].pass_Color;
		 
		    EmitVertex();
		}
	}
}