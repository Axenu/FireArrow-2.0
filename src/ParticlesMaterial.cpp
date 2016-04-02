#include "ParticlesMaterial.h"

ParticlesMaterial::ParticlesMaterial() {
	this->shader = new FAShader("particle","particle","particle");
	
	VPLocation = glGetUniformLocation(this->shader->shaderProgram, "VPMatrix");
	cameraPositionLocation = glGetUniformLocation(this->shader->shaderProgram, "cameraPosition");
	
	if (VPLocation == -1) { std::cout << "VPLocation failed!" << std::endl; }
	if (cameraPositionLocation == -1) { std::cout << "cameraPositionLocation failed!" << std::endl; }
	
}

ParticlesMaterial::~ParticlesMaterial() {
	
}

void ParticlesMaterial::bind() {
	glDisable(GL_CULL_FACE);
	glm::vec3 cameraPos = camera->getPosition();
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(VPLocation, 1, GL_FALSE, &this->viewProjectionMatrix[0][0]);
	glUniform3fv(cameraPositionLocation, 1, &cameraPos[0]);
}

void ParticlesMaterial::setViewProjectionwMatrix(glm::mat4 &VPMatrix) {
	this->viewProjectionMatrix = VPMatrix;
}