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
	std::string getMaterialOutput();
	std::string getLightOutput();
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
	std::string materialOutput;
	std::string lightOutput;
	std::string fragmentOutput;
	// std::map<std::string, FAMaterialComponent *> requirements;
	std::vector<FAMaterialComponent *> requirements;
	bool modelData;
	
};

class FAVertexPositionComponent : public FAMaterialComponent {
public:
	FAVertexPositionComponent();
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

class FAVertexColorComponent : public FAMaterialComponent {
public:
	FAVertexColorComponent();
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
	float *ambient;
	glm::vec3 *direction;
	glm::vec4 *color;

	// GLint ambientLocation;
	GLint directionLocation;
	GLint colorLocation;

	bool hasShadow;

public:
	FADirectionalLightComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);

	void setColor(glm::vec4 *color);
	void setDirection(glm::vec3 *direction);
	// void setAmbientComponent(float *ambientComponent);
	void setShadow(bool shadow);
};

class FAAmbientLightComponent : public FAMaterialComponent {
private:
	float *ambient;
	glm::vec4 *color;
	glm::vec4 finalColor;

	GLint colorLocation;

public:
	FAAmbientLightComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);

	void setColor(glm::vec4 *color);
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
	GLuint *texture;
public:
	FATextureComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);

	void setTexture(GLuint texture);
	void setTexture(GLuint *texture);
};

class FATextureArrayComponent : public FAMaterialComponent {
private:
	GLint textureUniformLocation;
	GLuint *texture;
	int layer;
public:
	FATextureArrayComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);

	void setTexture(GLuint texture);
	void setTexture(GLuint *texture);
	void setLayer(int layer);
};

class FACSMComponent : public FAMaterialComponent {
private:
	GLuint *texture;
	GLint textureUniformLocation;
	GLint inverseShadowMatrixUniformLocation;
	int *frustums;
	glm::mat4 *inverseShadowMatrix;
public:
	FACSMComponent();
	void setAttribute(std::string name, float value);
	void bind();
	void setUpLocations(GLint shaderProgram);

	void setTexture(GLuint *texture);
	void setFrustums(int *frustums);
	void setInverseShadowMatrix(glm::mat4 *inverseTextureMatrix);
};

#endif