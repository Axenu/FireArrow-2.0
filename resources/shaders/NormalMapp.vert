#version 400 core 

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_UV;
layout(location = 2) in vec3 in_Normal;
layout(location = 3) in vec3 in_Tangent;
layout(location = 4) in vec3 in_Bitangent;

out vec4 pass_Position;
out vec3 pass_lightDirection;
out vec3 pass_PointLightDirection;
out vec3 pass_ViewDirection;
out vec2 pass_UV;


uniform vec3 lightDirection;
uniform mat4 MVPMatrix;
uniform mat4 ModelMatrix;
uniform vec3 cameraPosition;

void main() {
    vec3 pointLightPosition = vec3(9,1,0);

	pass_Position = ModelMatrix * vec4(in_Position.xyz, 1.0);
	pass_UV = in_UV;

	vec3 T = normalize(ModelMatrix * vec4(in_Tangent, 0.0)).xyz;
	vec3 B = normalize(ModelMatrix * vec4(in_Bitangent, 0.0)).xyz;
	vec3 N = normalize(ModelMatrix * vec4(in_Normal, 0.0)).xyz;

	mat3 TBNMatrix = mat3(T,B,N);
	pass_lightDirection = lightDirection;
	pass_lightDirection *= TBNMatrix;
	pass_PointLightDirection = pointLightPosition - pass_Position.xyz;
	pass_PointLightDirection *= TBNMatrix;
	pass_ViewDirection = cameraPosition-pass_Position.xyz;
	pass_ViewDirection *= TBNMatrix;
	gl_Position = MVPMatrix * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
}