#include "FAMaterial.h"

FAMaterial::FAMaterial() {
	// this->modelMatrix = glm::mat4();
	this->shader = new FAShader("Basic");
	glUseProgram(this->shader->shaderProgram);
	MVPLocation = glGetUniformLocation(this->shader->shaderProgram, "MVPMatrix");
	if (MVPLocation == -1) {
		std::cout << "MVPLocation failed!" << std::endl;
	}
	glUseProgram(0);
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

	glm::mat4 MVPMatrix = modelMatrix * viewProjectionMatrix;
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

FAMaterial::~FAMaterial() {
	
}