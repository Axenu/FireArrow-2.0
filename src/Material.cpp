#include "Material.h"

Material::Material() {
	this->shader = new FAShader("Simple");
	this->lightDirection = glm::vec3(0,1,1);

	MVPLocation = glGetUniformLocation(this->shader->shaderProgram, "MVPMatrix");
	LightDirectionLocation = glGetUniformLocation(this->shader->shaderProgram, "lightDirection");
	modelMatrixLocation = glGetUniformLocation(this->shader->shaderProgram, "ModelMatrix");
	normalMatrixLocation = glGetUniformLocation(this->shader->shaderProgram, "NormalMatrix");
	shadowMapLocation = glGetUniformLocation(this->shader->shaderProgram, "shadowMap");
	inverseShadowMatrixLocation = glGetUniformLocation(this->shader->shaderProgram, "inverseShadowMatrix");

	if (MVPLocation == -1) { std::cout << "MVPLocation failed!" << std::endl; }
	if (LightDirectionLocation == -1) { std::cout << "LightDirectionLocation failed!" << std::endl; }
	if (modelMatrixLocation == -1) { std::cout << "modelMatrixLocation failed!" << std::endl; }
	if (normalMatrixLocation == -1) { std::cout << "normalMatrixLocation failed!" << std::endl; }
	if (shadowMapLocation == -1) { std::cout << "shadowMapLocation failed!" << std::endl; }
	if (inverseShadowMatrixLocation == -1) { std::cout << "inverseShadowMatrixLocation failed!" << std::endl; }
	
	this->shadowShader = new FAShader("shadow");
	
	shadowMVPMatrixLocation = glGetUniformLocation(this->shadowShader->shaderProgram, "MVPMatrix");
	if (shadowMVPMatrixLocation == -1) { std::cout << "shadowMVPMatrixLocation failed!" << std::endl; }
}

Material::~Material() {

}

//render order:
// m->getMaterial().setViewProjectionwMatrix(&(parent->getCamera()->VPMatrix));
// m->getMaterial().bind();
// m->getMesh().render();

void Material::bind() {
	glm::mat4 m = this->viewProjectionMatrix * this->modelMatrix;
	glm::mat4 n = glm::transpose(glm::inverse(this->modelMatrix));
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &m[0][0]);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &this->modelMatrix[0][0]);
	glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, &n[0][0]);
	glUniform3fv(LightDirectionLocation, 1, &lightDirection[0]);
	//shadowmap
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D_ARRAY, *this->texture);
	glUniform1i(shadowMapLocation, 2);
	glUniformMatrix4fv(inverseShadowMatrixLocation, (GLsizei) 4, GL_FALSE, &inverseShadowMatrix[0][0][0]);
}

void Material::bindShadow() {
	glm::mat4 m = this->viewProjectionMatrix * this->modelMatrix;
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(shadowMVPMatrixLocation, 1, GL_FALSE, &m[0][0]);
}

void Material::setLightDirection(glm::vec3 &direction) {
	this->lightDirection = direction;
}

void Material::setViewProjectionwMatrix(glm::mat4 &VPMatrix) {
	this->viewProjectionMatrix = VPMatrix;
}

void Material::setModelMatrix(glm::mat4 &modelMatrix) {
	this->modelMatrix = modelMatrix;
}
void Material::setTexture(GLuint *texture) {
	this->texture = texture;
}

void Material::setInverseShadowMatrix(glm::mat4 *inverseTextureMatrix) {
	this->inverseShadowMatrix = inverseTextureMatrix;
}