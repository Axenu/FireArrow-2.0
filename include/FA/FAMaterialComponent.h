#ifndef __First__FAMaterialComponent__
#define __First__FAMaterialComponent__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <string>
#include <map>
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


protected:

	std::string name;
	std::string vertexIO;
	std::string vertexMain;
	std::string fragmentIO;
	std::string fragmentMain;
	std::string fragmentOutput;
	std::map<std::string, FAMaterialComponent *> requirements;
	
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
};

#endif