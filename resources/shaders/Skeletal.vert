#version 400 core 

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec3 in_Color;
layout(location = 3) in vec4 in_Index;
layout(location = 4) in vec4 in_Weight;

out vec4 pass_Position;
out vec4 pass_Normal;
out vec4 pass_Color;


uniform mat4 MVPMatrix;
uniform mat4 ModelMatrix;
uniform mat4 NormalMatrix;
uniform mat4 bones[4];

void main() {
	//skinning
	mat4 skintransform = (bones[int(in_Index.x)] * in_Weight.x);
	skintransform = skintransform + (bones[int(in_Index.y)] * in_Weight.y);
	skintransform = skintransform + (bones[int(in_Index.z)] * in_Weight.z);
	skintransform = skintransform + (bones[int(in_Index.w)] * in_Weight.w);

	pass_Position = ModelMatrix * (skintransform * vec4(in_Position.xyz, 1.0));
	pass_Normal = NormalMatrix * skintransform * vec4(in_Normal, 0.0);
	pass_Color = vec4(in_Color, 1.0);
	gl_Position = MVPMatrix * (skintransform * vec4(in_Position.xyz, 1.0));
}