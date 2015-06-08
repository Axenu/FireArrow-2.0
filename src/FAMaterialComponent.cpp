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

void FAVertexColorComponent::setUpLocations(GLint shaderProgram) {

}

//Vertex normal material

FAVertexNormalComponent::FAVertexNormalComponent() {
	vertexIO = "layout(location = 1) in vec3 in_Normal;\nout vec4 pass_Normal;\n";
	vertexMain = "pass_Normal = vec4(in_Normal, 1.0);\n";
	fragmentIO = "in vec4 pass_Normal;\n";
	fragmentMain = "";
	fragmentOutput = "OTHER_OUT";
	name = "vertexNormal";
}

void FAVertexNormalComponent::setAttribute(std::string name, float value) {

}

void FAVertexNormalComponent::bind() {

}

void FAVertexNormalComponent::setUpLocations(GLint shaderProgram) {

}

//Directional light material

FADirectionalLightComponent::FADirectionalLightComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform float ambient;\nuniform vec4 diffuseColor;\nuniform vec3 direction;\n";
	fragmentMain = "vec3 normal = normalize(pass_Normal.xyz);\n"
    "vec3 lightDir = normalize(direction);\n"
    "float lambertian = max(dot(lightDir,normal), 0.0);\n";
	fragmentOutput = "(OTHER_OUT) * (ambient * vec4(1,1,1,1) + lambertian * diffuseColor)";
	name = "Directional light";
}

void FADirectionalLightComponent::setAttribute(std::string name, float value) {
	// if (name == "ambient") {
	// 	this->ambient = value;
	// } else if (name == "diffuseColor.r") {
	// 	this->diffuseColor.r = value;
	// } else if (name == "diffuseColor.g") {
	// 	this->diffuseColor.g = value;
	// } else if (name == "diffuseColor.b") {
	// 	this->diffuseColor.b = value;
	// }
}

void FADirectionalLightComponent::bind() {
	glUniform1f(ambientLocation, ambient);
	glUniform4fv(colorLocation, 1, &color[0]);
	glUniform3fv(directionLocation, 1, &direction[0]);
}

void FADirectionalLightComponent::setUpLocations(GLint shaderProgram) {
	ambientLocation = glGetUniformLocation(shaderProgram, "ambient");
	colorLocation = glGetUniformLocation(shaderProgram, "diffuseColor");
	directionLocation = glGetUniformLocation(shaderProgram, "direction");

	ambient = 0.5;
	direction = glm::vec3(1,1,0);
	color = glm::vec4(1,0,1,1);

	if (ambientLocation == -1)
		std::cout << "Error getting ambientLocation in " << name << " component!" << std::endl;
	if (colorLocation == -1)
		std::cout << "Error getting colorLocation in " << name << " component!" << std::endl;
	if (directionLocation == -1)
		std::cout << "Error getting directionLocation in " << name << " component!" << std::endl;

}





