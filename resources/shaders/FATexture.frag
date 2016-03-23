#version 400 core

uniform sampler2DArray text;

in vec2 pass_UV;

out vec4 Frag_Data;

void main() {
	vec4 textureColor = vec4(1,1,1,1); 
	textureColor.x = texture(text, vec3(pass_UV, 0)).r;
	textureColor.y = texture(text, vec3(pass_UV, 1)).r;
	textureColor.z = texture(text, vec3(pass_UV, 2)).r;
	textureColor.w = texture(text, vec3(pass_UV, 3)).r;
    // Frag_Data = texture(text, vec3(pass_UV,2));
    Frag_Data = textureColor;
    // Frag_Data = vec4(1);
}