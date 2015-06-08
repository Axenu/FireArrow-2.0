#include "FAMaterialComponent.h"

FAMaterialComponent::FAMaterialComponent() {

}

FAMaterialComponent::~FAMaterialComponent() {

}

void FAMaterialComponent::setAttribute(std::string name, float value) {

}

std::string FAMaterialComponent::getVertexIO() {
	return this->vertexIO;
}

std::string FAMaterialComponent::getVertexMain() {
	return this->vertexMain;
}

std::string FAMaterialComponent::getFragmentIO() {
	return this->fragmentIO;
}

std::string FAMaterialComponent::getFragmentMain() {
	return this->fragmentMain;
}

std::string FAMaterialComponent::getFragmentMainOutput() {
	return this->fragmentOutput;
}

//Vertex Color material

FAVertexColorComponent::FAVertexColorComponent() {
	vertexIO = "layout(location = 2) in vec3 in_Color;\nout vec4 pass_Color;\n";
	vertexMain = "pass_Color = vec4(in_Color, 1.0);\n";
	fragmentIO = "in vec4 pass_Color;\n";
	fragmentMain = "";
	fragmentOutput = "(OTHER_OUT) * pass_Color";
	name = "vertexColor";
}

void FAVertexColorComponent::setAttribute(std::string name, float value) {

}

void FAVertexColorComponent::bind() {

}

//Vertex normal material

FAVertexNormalComponent::FAVertexNormalComponent() {
	vertexIO = "layout(location = 1) in vec3 in_Normal;\nout vec4 pass_Normal;\n";
	vertexMain = "pass_Normal = vec4(in_Normal, 1.0);\n";
	fragmentIO = "in vec4 pass_Normal;\n";
	fragmentMain = "";
	fragmentOutput = "(OTHER_OUT) * pass_Normal";
	name = "vertexNormal";
}

void FAVertexNormalComponent::setAttribute(std::string name, float value) {

}

void FAVertexNormalComponent::bind() {

}