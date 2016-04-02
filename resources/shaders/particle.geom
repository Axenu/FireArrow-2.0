#version 400 core

layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;

in vec3 pass_Offset[];

uniform mat4 VPMatrix;
uniform vec3 cameraPosition;
 
 void main() {

 	//calculate transformation
 	// vec3 right = vec3(VMatrix[0][0], VMatrix[1][0], VPMatrix[2][0]);
 	// vec3 up = vec3(VMatrix[0][1], VMatrix[1][1], VPMatrix[2][1]);
 	vec3 look = normalize(cameraPosition - pass_Offset[0]);
 	vec3 right = cross(look, vec3(0,1,0));
 	vec3 up = cross(right, look);
 	// look = vec3(0,0,1);
 	// up = vec3(0,1,0);
 	// right = vec3(1,0,0);

    gl_Position = VPMatrix * vec4(right * gl_in[0].gl_Position.x + up * gl_in[0].gl_Position.y + look * gl_in[0].gl_Position.z, 1.0);
    EmitVertex();
    gl_Position = VPMatrix * vec4(right * gl_in[1].gl_Position.x + up * gl_in[1].gl_Position.y + look * gl_in[1].gl_Position.z, 1.0);
    EmitVertex();
    gl_Position = VPMatrix * vec4(right * gl_in[2].gl_Position.x + up * gl_in[2].gl_Position.y + look * gl_in[2].gl_Position.z, 1.0);
    EmitVertex();
    // gl_Position = VPMatrix * gl_in[0].gl_Position;
    // EmitVertex();
    // gl_Position = VPMatrix * gl_in[1].gl_Position;
    // EmitVertex();
    // gl_Position = VPMatrix * gl_in[2].gl_Position;
    // EmitVertex();
    EndPrimitive();
}