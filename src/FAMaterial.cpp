#include "FAMaterial.h"

FAMaterial::FAMaterial() {

	this->vertexIO = "#version 400 core \n uniform mat4 MVPMatrix;"
		"layout(location = 0) in vec3 in_Position;\n"
		"layout(location = 1) in vec3 in_Normal;\n"
		"layout(location = 2) in vec3 in_Color;\n"
		"out vec4 pass_Normal;\n"
		"out vec4 pass_Color;\n";
	this->vertexMain = "pass_Normal = normalize(vec4(in_Normal, 1.0));\n"
	    "pass_Color = vec4(in_Color, 1.0);\n"
	    "gl_Position = MVPMatrix * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);\n";

	this->fragmentIO = "#version 400 core \n in vec4 pass_Normal;\n in vec4 pass_Color;\n out vec4 Frag_Data;\n";
	this->fragmentMain = "";
	this->fragmentOutput = "Frag_Data = pass_Color;\n";

	// this->modelMatrix = glm::mat4();
	// this->shader = new FAShader("Basic");
	buildShader();
	glUseProgram(this->shader->shaderProgram);
	MVPLocation = glGetUniformLocation(this->shader->shaderProgram, "MVPMatrix");
	if (MVPLocation == -1) {
		std::cout << "MVPLocation failed!" << std::endl;
	}
	glUseProgram(0);
}

void FAMaterial::buildShader() {

	std::string vertexShader = "", fragmentShader = "";

	vertexShader += this->vertexIO;
	vertexShader += "void main() {\n";
	vertexShader += this->vertexMain;
	vertexShader += "}\n";

	fragmentShader += this->fragmentIO;
	fragmentShader += "void main() {\n";
	fragmentShader += this->fragmentMain;
	fragmentShader += this->fragmentOutput;
	fragmentShader += "}\n";

	this->shader = new FAShader(&vertexShader, &fragmentShader);

}

// void FAMaterial::setAttribute(std::string name, float value) {
// 	std::string compName = name.substr(name.find("."))[0];
// 	for (FAMaterialComponent *c : components) {
// 		if (c->getName() == compName) {
// 			c->setAttribute(name.substr(name.find("."))[1]);
// 			break;
// 		}
// 	}
// 	//check all possible commands //supposedly prefix only
// 	//if found send to the component with suffix
// }

void FAMaterial::bind() {
	// for (FAMaterialComponent *c : components) {
	// 	c->render();
	// }
	//setup ALL attributes, depth test, uniforms etc.

	glm::mat4 MVPMatrix = viewProjectionMatrix * modelMatrix;
	// glm::mat4 MVPMatrix = glm::mat4();
	// std::cout << "glm::mat4: " << std::endl;
	// std::cout << MVPMatrix[0][0] << ", " << MVPMatrix[0][1] << ", " << MVPMatrix[0][2] << ", " << MVPMatrix[0][3] << std::endl;
	// std::cout << MVPMatrix[1][0] << ", " << MVPMatrix[1][1] << ", " << MVPMatrix[1][2] << ", " << MVPMatrix[1][3] << std::endl;
	// std::cout << MVPMatrix[2][0] << ", " << MVPMatrix[2][1] << ", " << MVPMatrix[2][2] << ", " << MVPMatrix[2][3] << std::endl;
	// std::cout << MVPMatrix[3][0] << ", " << MVPMatrix[3][1] << ", " << MVPMatrix[3][2] << ", " << MVPMatrix[3][3] << std::endl;
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &MVPMatrix[0][0]);
}

void FAMaterial::setViewProjectionwMatrix(glm::mat4 *VPMatrix) {
	this->viewProjectionMatrix = *VPMatrix;
}

void FAMaterial::setModelMatrix(glm::mat4 &modelMatrix) {
	this->modelMatrix = modelMatrix;
}

FAMaterial::~FAMaterial() {
	
}