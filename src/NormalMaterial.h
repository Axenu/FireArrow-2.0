//
//  NormalMaterial.hpp
//  FA
//
//  Created by Simon Nilsson on 3/25/16.
//  Copyright © 2016 Axenu. All rights reserved.
//

#ifndef __First__NormalMaterial__
#define __First__NormalMaterial__

#define GLM_FORCE_RADIANS

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <sstream>
#include <FA/FAMaterial.h>
#include <FA/FATexture.h>

class NormalMaterial : public FAMaterial {
	
private:
	// std::vector<FAMaterialComponent*> components;
	FAShader *shader;
	FAShader *shadowShader;
	glm::mat4 viewProjectionMatrix;
	glm::mat4 modelMatrix;
	glm::vec3 lightDirection;
	GLuint *shadowMap;
	glm::mat4 *inverseShadowMatrix;
	GLuint texture;
	GLuint bumpMap;
	
	GLint MVPLocation;
	GLint modelMatrixLocation;
	GLint normalMatrixLocation;
	GLint LightDirectionLocation;
	GLint shadowMapLocation;
	GLint inverseShadowMatrixLocation;
	GLint cameraPositionLocation;
	//shadow
	GLint shadowMVPMatrixLocation;
	GLint shadowBonesLoaction;
	//texture
	GLint textureLocation;
	GLint bumpMapLocation;
	
	// GLint MLocation;
	
	//dynamic materials:
	// std::string vertexIO;
	// std::string vertexMain;
	// std::string fragmentIO;
	// std::string fragmentMain;
	// std::string fragmentOutput;
	
	// bool hasColor = false; //TODO remove
	
	// bool isBuilt = false;
	// bool isCreated = false;
	
	// void buildShader();
	// FAMaterialComponent* getComponentByName(std::string name);
	
public:
	NormalMaterial();
	~NormalMaterial();
	
	void bind();
	void bindShadow();
	void setLightDirection(glm::vec3 &direction);
	void setViewProjectionwMatrix(glm::mat4 &VPMatrix);
	void setModelMatrix(glm::mat4 &modelMatrix);
	void setShadowMap(GLuint *texture);
	void setInverseShadowMatrix(glm::mat4 *inverseTextureMatrix);
	void setOBJMaterial(std::string library, std::string material);
};

#endif
