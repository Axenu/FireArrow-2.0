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
	std::vector<FAMaterialComponent *> pendingComponents;
	std::vector<FAMaterialComponent *> avaliableVertexComponents;

	GLint MVPLocation;
	GLint MLocation;

	//dynamic materials:
	std::string vertexIO;
	std::string vertexMain;
	std::string fragmentIO;
	std::string fragmentMain;
	std::string fragmentOutput;

	bool hasColor = false; //TODO remove
	
	bool isBuilt = false;
	bool isCreated = false;

	void buildShader();
	FAMaterialComponent* getComponentByName(std::string name);

public:
	FAMaterial();
	~FAMaterial();

	void setColor(glm::vec4 &color);
	void setDirectionalLight(glm::vec3 &direction, glm::vec4 &color, float ambientComponent);
	void setTexture(GLuint texture);
	void setTexture(GLuint *texture);
	void setTextureArray(GLuint *texture, int layer);

	// void hasVertexPosition(bool value);
	// void hasVertexColor(bool value);
	// void hasVertexNormal(bool value);
	// void hasVertexUV(bool value);
	void addVertexComponents(std::vector<FAMaterialComponent *> *components);

	bool addMaterialComponent(FAMaterialComponent *component);
	void setAttribute(std::string name, float value);
	void create();
	//check requirements
	//add new requirements
	//addThis

	virtual void bind() =0;
	virtual void setViewProjectionwMatrix(glm::mat4 &VPMatrix) =0;
	virtual void setModelMatrix(glm::mat4 &modelMatrix) =0;
};

#endif