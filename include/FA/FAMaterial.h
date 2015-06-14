#ifndef __First__FAMaterial__
#define __First__FAMaterial__

#define GLM_FORCE_RADIANS

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include "FAShader.h"
#include "FAMaterialComponent.h"

class FAMaterial {

private:
	// std::vector<FAMaterialComponent*> components;
	FAShader *shader;
	glm::mat4 viewProjectionMatrix;
	glm::mat4 modelMatrix;
	std::vector<FAMaterialComponent *> components;

	GLint MVPLocation;

	//dynamic materials:
	std::string vertexIO;
	std::string vertexMain;
	std::string fragmentIO;
	std::string fragmentMain;
	std::string fragmentOutput;

	void buildShader();

public:
	FAMaterial();
	~FAMaterial();
	// void addMaterial();
	void setAttribute(std::string name, float value);
	//check requirements
	//add new requirements
	//addThis

	void bind();
	void setViewProjectionwMatrix(glm::mat4 *VPMatrix);
	void setModelMatrix(glm::mat4 &modelMatrix);
};

#endif