#ifndef __First__FAMaterialComponent__
#define __First__FAMaterialComponent__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "FAShader.h"

class FAMaterialComponent {

private:

public:
	FAMaterialComponent();
	~FAMaterialComponent();
	std::string getVertexIO();
	std::string getVertexMain();
	std::string getFragmentIO();
	std::string getFragmentMain();
	std::string getFragmentMainOutput();
	std::string getName();

	virtual void setAttribute(std::string name, float value) = 0;
	virtual void bind() = 0;
	virtual void setUpLocations(GLint shaderProgram) = 0;

	std::vector<FAMaterialComponent *> *getRequirements();
	bool requiresModelData();

protected:

	std::string name;
	std::string vertexIO;
	std::string vertexMain;
	std::string fragmentIO;
	std::string fragmentMain;
	std::string fragmentOutput;
	// std::map<std::string, FAMaterialComponent *> requirements;
	std::vector<FAMaterialComponent *> requirements;
	bool modelData;
	
};

class FAVertexColorComponent : public FAMaterialComponent {
public:
	FAVertexColorComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);
};

class FAVertexNormalComponent : public FAMaterialComponent {
public:
	FAVertexNormalComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);
};

class FAVertexUVComponent : public FAMaterialComponent {
public:
	FAVertexUVComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);
};

class FADirectionalLightComponent : public FAMaterialComponent {
private:
	float ambient;
	glm::vec3 direction;
	glm::vec4 color;

	GLint ambientLocation;
	GLint directionLocation;
	GLint colorLocation;


public:
	FADirectionalLightComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);

	void setColor(glm::vec4 &color);
	void setDirection(glm::vec3 direction);
	void setAmbientComponent(float ambientComponent);
};

class FAColorComponent : public FAMaterialComponent {
private:
	GLint colorUniformLocation;
	glm::vec4 color;
public:
	FAColorComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);

	void setColor(glm::vec4 &color);
};

class FATextureComponent : public FAMaterialComponent {
private:
	GLint textureUniformLocation;
	GLuint texture;
public:
	FATextureComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);

	void setTexture(GLuint texture);
};

#endif