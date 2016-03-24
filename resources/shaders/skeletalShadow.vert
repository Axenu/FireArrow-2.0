#version 400 core
layout(location = 0) in vec3 in_Position;
layout(location = 3) in vec4 in_Index;
layout(location = 4) in vec4 in_Weight;

uniform mat4 MVPMatrix;
uniform mat4 bones[4];

void main() {
	//skinning
	int index = int(in_Index.x);
	vec4 skintransform = (bones[index] * in_Weight.x) * vec4(in_Position.xyz, 1.0);
	index = int(in_Index.y);
	skintransform = skintransform + (bones[index] * in_Weight.y) * vec4(in_Position.xyz, 1.0);
	index = int(in_Index.z);
	skintransform = skintransform + (bones[index] * in_Weight.z) * vec4(in_Position.xyz, 1.0);
	index = int(in_Index.w);
	skintransform = skintransform + (bones[index] * in_Weight.w) * vec4(in_Position.xyz, 1.0);
	
	gl_Position = MVPMatrix * skintransform;
}