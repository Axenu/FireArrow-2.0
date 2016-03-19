#include "Material.h"

Material::Material() {
	this->shader = new FAShader("Simple");

	MVPLocation = glGetUniformLocation(this->shader->shaderProgram, "MVPMatrix");

	if (MVPLocation == -1) {
		std::cout << "MVPLocation failed!" << std::endl;
	}
	std::cout << "main " << std::endl;
}

Material::~Material() {

}

//render order:
// m->getMaterial().setViewProjectionwMatrix(&(parent->getCamera()->VPMatrix));
// m->getMaterial().bind();
// m->getMesh().render();

void Material::bind() {
	glm::mat4 m = this->viewProjectionMatrix * this->modelMatrix;
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &m[0][0]);
	std::cout << "vind" << std::endl;
}

void Material::setViewProjectionwMatrix(glm::mat4 &VPMatrix) {
	this->viewProjectionMatrix = VPMatrix;
	std::cout << "vind" << std::endl;
}

void Material::setModelMatrix(glm::mat4 &modelMatrix) {
	this->modelMatrix = modelMatrix;
	std::cout << "vind" << std::endl;
}