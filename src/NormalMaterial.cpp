#include "NormalMaterial.h"



NormalMaterial::NormalMaterial() {
	
	this->shader = new FAShader("NormalMapp");
	this->lightDirection = glm::vec3(0,1,1);
	
	MVPLocation = glGetUniformLocation(this->shader->shaderProgram, "MVPMatrix");
	LightDirectionLocation = glGetUniformLocation(this->shader->shaderProgram, "lightDirection");
	modelMatrixLocation = glGetUniformLocation(this->shader->shaderProgram, "ModelMatrix");
	normalMatrixLocation = glGetUniformLocation(this->shader->shaderProgram, "NormalMatrix");
	shadowMapLocation = glGetUniformLocation(this->shader->shaderProgram, "shadowMap");
	inverseShadowMatrixLocation = glGetUniformLocation(this->shader->shaderProgram, "inverseShadowMatrix");
	cameraPositionLocation = glGetUniformLocation(this->shader->shaderProgram, "cameraPosition");
	textureLocation = glGetUniformLocation(this->shader->shaderProgram, "text");
	bumpMapLocation = glGetUniformLocation(this->shader->shaderProgram, "bump");
	
	if (MVPLocation == -1) { std::cout << "MVPLocation failed!" << std::endl; }
	if (LightDirectionLocation == -1) { std::cout << "LightDirectionLocation failed!" << std::endl; }
	if (modelMatrixLocation == -1) { std::cout << "modelMatrixLocation failed!" << std::endl; }
	if (normalMatrixLocation == -1) { std::cout << "normalMatrixLocation failed!" << std::endl; }
	if (shadowMapLocation == -1) { std::cout << "shadowMapLocation failed!" << std::endl; }
	if (inverseShadowMatrixLocation == -1) { std::cout << "inverseShadowMatrixLocation failed!" << std::endl; }
	if (cameraPositionLocation == -1) { std::cout << "cameraPositionLocation failed!" << std::endl; }
	if (textureLocation == -1) { std::cout << "textureLocation failed!" << std::endl; }
	if (bumpMapLocation == -1) { std::cout << "bumpMapLocation failed!" << std::endl; }
	
	this->shadowShader = new FAShader("shadow");
	
	shadowMVPMatrixLocation = glGetUniformLocation(this->shadowShader->shaderProgram, "MVPMatrix");
	if (shadowMVPMatrixLocation == -1) { std::cout << "shadowMVPMatrixLocation failed!" << std::endl; }
}

NormalMaterial::~NormalMaterial() {
	
}

void NormalMaterial::bind() {
//	glDisable(GL_CULL_FACE);
	glm::mat4 m = this->viewProjectionMatrix * this->modelMatrix;
	glm::mat4 n = glm::transpose(glm::inverse(this->modelMatrix));
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &m[0][0]);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &this->modelMatrix[0][0]);
	glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, &n[0][0]);
	glUniform3fv(LightDirectionLocation, 1, &lightDirection[0]);
	glUniform3fv(cameraPositionLocation, 1, &this->camera->FANode::getPosition()[0]);
	//shadowmap
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, *this->shadowMap);
	glUniform1i(shadowMapLocation, 0);
	glUniformMatrix4fv(inverseShadowMatrixLocation, (GLsizei) 4, GL_FALSE, &inverseShadowMatrix[0][0][0]);
	
	//texture and bumpmap
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glUniform1i(textureLocation, 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, this->bumpMap);
	glUniform1i(bumpMapLocation, 2);
}

void NormalMaterial::bindShadow() {
	glm::mat4 m = this->viewProjectionMatrix * this->modelMatrix;
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(shadowMVPMatrixLocation, 1, GL_FALSE, &m[0][0]);
}

void NormalMaterial::setLightDirection(glm::vec3 &direction) {
	this->lightDirection = direction;
}

void NormalMaterial::setViewProjectionwMatrix(glm::mat4 &VPMatrix) {
	this->viewProjectionMatrix = VPMatrix;
}

void NormalMaterial::setModelMatrix(glm::mat4 &modelMatrix) {
	this->modelMatrix = modelMatrix;
}

void NormalMaterial::setShadowMap(GLuint *texture) {
	this->shadowMap = texture;
}

void NormalMaterial::setInverseShadowMatrix(glm::mat4 *inverseTextureMatrix) {
	this->inverseShadowMatrix = inverseTextureMatrix;
}

void NormalMaterial::setOBJMaterial(std::string library, std::string material) {
	std::ifstream file (library);
	if (!file.is_open()) {
		std::cout << "File " << library << "not found!" << std::endl;
		return;
	}
	std::string line;
	std::string option;
	std::string path;
	while (!file.eof()) {
		option = "#";
		getline(file, line);
		std::stringstream ss(line);
		ss >> option;
		if (option == "map_Bump") {
			ss >> path;
			this->bumpMap = FATexture::createTexture(path.c_str());
		} else if (option == "map_Kd") {
			ss >> path;
			this->texture =FATexture::createTexture(path.c_str());
		}
		
	}
}






