#version 400 core

in vec2 pass_UV;

out vec4 Frag_Data;

uniform sampler2D text;
uniform float resolution;

void main() {

	vec4 sum = vec4(0.0);

	sum += texture(text, vec2(pass_UV.x - 4.0 * resolution, pass_UV.y)) * 0.0162162162;
	sum += texture(text, vec2(pass_UV.x - 3.0 * resolution, pass_UV.y)) * 0.0540540541;
	sum += texture(text, vec2(pass_UV.x - 2.0 * resolution, pass_UV.y)) * 0.1216216216;
	sum += texture(text, vec2(pass_UV.x - 1.0 * resolution, pass_UV.y)) * 0.1945945946;

	sum += texture(text, vec2(pass_UV.x, pass_UV.y)) * 0.2270270270;

	sum += texture(text, vec2(pass_UV.x + 1.0 * resolution, pass_UV.y)) * 0.1945945946;
	sum += texture(text, vec2(pass_UV.x + 2.0 * resolution, pass_UV.y)) * 0.1216216216;
	sum += texture(text, vec2(pass_UV.x + 3.0 * resolution, pass_UV.y)) * 0.0540540541;
	sum += texture(text, vec2(pass_UV.x + 4.0 * resolution, pass_UV.y)) * 0.0162162162;

	Frag_Data = vec4(sum.xyz, 1.0);
}