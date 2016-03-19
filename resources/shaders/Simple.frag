#version 400 core 

in vec4 pass_Color;

out vec4 Frag_Data;

void main() {
	Frag_Data = pass_Color;
}
