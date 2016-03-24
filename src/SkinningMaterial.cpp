#include "SkinningMaterial.h"

SkinningMaterial::SkinningMaterial() {
	this->shader = new FAShader("Skeletal");
	this->lightDirection = glm::vec3(0,1,1);
	
	MVPLocation = glGetUniformLocation(this->shader->shaderProgram, "MVPMatrix");
	LightDirectionLocation = glGetUniformLocation(this->shader->shaderProgram, "lightDirection");
	modelMatrixLocation = glGetUniformLocation(this->shader->shaderProgram, "ModelMatrix");
	shadowMapLocation = glGetUniformLocation(this->shader->shaderProgram, "shadowMap");
	inverseShadowMatrixLocation = glGetUniformLocation(this->shader->shaderProgram, "inverseShadowMatrix");
	bonesLocation = glGetUniformLocation(this->shader->shaderProgram, "bones");
	
	if (MVPLocation == -1) { std::cout << "MVPLocation failed!" << std::endl; }
	if (LightDirectionLocation == -1) { std::cout << "LightDirectionLocation failed!" << std::endl; }
	if (modelMatrixLocation == -1) { std::cout << "modelMatrixLocation failed!" << std::endl; }
	if (shadowMapLocation == -1) { std::cout << "shadowMapLocation failed!" << std::endl; }
	if (inverseShadowMatrixLocation == -1) { std::cout << "inverseShadowMatrixLocation failed!" << std::endl; }
	if (bonesLocation == -1) { std::cout << "bonesLocation failed!" << std::endl; }
	
	this->shadowShader = new FAShader("skeletalShadow", "shadow");
	
	shadowMVPMatrixLocation = glGetUniformLocation(this->shadowShader->shaderProgram, "MVPMatrix");
	shadowBonesLoaction = glGetUniformLocation(this->shadowShader->shaderProgram, "bones");
	if (shadowMVPMatrixLocation == -1) { std::cout << "shadowMVPMatrixLocation failed!" << std::endl; }
	if (shadowBonesLoaction == -1) { std::cout << "shadowBonesLoaction failed!" << std::endl; }
}

SkinningMaterial::~SkinningMaterial() {
	
}

//render order:
// m->getMaterial().setViewProjectionwMatrix(&(parent->getCamera()->VPMatrix));
// m->getMaterial().bind();
// m->getMesh().render();

void SkinningMaterial::bind() {
	glm::mat4 m = this->viewProjectionMatrix * this->modelMatrix;
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &m[0][0]);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &this->modelMatrix[0][0]);
	glUniform3fv(LightDirectionLocation, 1, &lightDirection[0]);
	//armature
	glUniformMatrix4fv(bonesLocation, (GLsizei) armature->getNumberOfBones(), GL_FALSE, armature->getAnimatedXForm());
	//shadowmap
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D_ARRAY, *this->texture);
	glUniform1i(shadowMapLocation, 2);
	glUniformMatrix4fv(inverseShadowMatrixLocation, (GLsizei) 4, GL_FALSE, &inverseShadowMatrix[0][0][0]);
}

void SkinningMaterial::bindShadow() {
	glm::mat4 m = this->viewProjectionMatrix * this->modelMatrix;
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(shadowMVPMatrixLocation, 1, GL_FALSE, &m[0][0]);
	//armature
	glUniformMatrix4fv(bonesLocation, (GLsizei) armature->getNumberOfBones(), GL_FALSE, armature->getAnimatedXForm());
}

void SkinningMaterial::setLightDirection(glm::vec3 &direction) {
	this->lightDirection = direction;
}

void SkinningMaterial::setViewProjectionwMatrix(glm::mat4 &VPMatrix) {
	this->viewProjectionMatrix = VPMatrix;
}

void SkinningMaterial::setModelMatrix(glm::mat4 &modelMatrix) {
	this->modelMatrix = modelMatrix;
}
void SkinningMaterial::setTexture(GLuint *texture) {
	this->texture = texture;
}

void SkinningMaterial::setInverseShadowMatrix(glm::mat4 *inverseTextureMatrix) {
	this->inverseShadowMatrix = inverseTextureMatrix;
}

void SkinningMaterial::setArmature(FAArmature *armature) {
	this->armature = armature;
}