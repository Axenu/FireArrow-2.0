#ifndef __First__FAMaterial__
#define __First__FAMaterial__

#define GLM_FORCE_RADIANS

#include <iostream>
#include <glm/glm.hpp>
#include "FAShader.h"
// #include "FAMaterialComponent.h"

class FAMaterial {

private:
	// std::vector<FAMaterialComponent*> components;
	FAShader *shader;
	glm::mat4 viewProjectionMatrix;
	glm::mat4 modelMatrix;

	GLint MVPLocation;
public:
	FAMaterial();
	~FAMaterial();
	// void addMaterial();
	// void setAttribute(std::string name, float value);
	//check requirements
	//add new requirements
	//addThis

	void bind();
	void setViewProjectionwMatrix(glm::mat4 *VPMatrix);
};

#endif