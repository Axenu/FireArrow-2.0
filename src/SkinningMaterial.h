#ifndef __First__SkinningMaterial__
#define __First__SkinningMaterial__

#define GLM_FORCE_RADIANS

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <FA/FAMaterial.h>
#include <FA/FAArmature.h>

class SkinningMaterial : public FAMaterial {
	
private:
	// std::vector<FAMaterialComponent*> components;
	FAShader *shader;
	FAShader *shadowShader;
	glm::mat4 viewProjectionMatrix;
	glm::mat4 modelMatrix;
	glm::vec3 lightDirection;
	GLuint *texture;
	glm::mat4 *inverseShadowMatrix;
	FAArmature *armature;
	// std::vector<FAMaterialComponent *> components;
	// std::vector<FAMaterialComponent *> pendingComponents;
	// std::vector<FAMaterialComponent *> avaliableVertexComponents;
	
	GLint MVPLocation;
	GLint modelMatrixLocation;
	GLint LightDirectionLocation;
	GLint shadowMapLocation;
	GLint inverseShadowMatrixLocation;
	GLint bonesLocation;
	//shadow
	GLint shadowMVPMatrixLocation;
	GLint shadowBonesLoaction;
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
	SkinningMaterial();
	~SkinningMaterial();
	
	// void setColor(glm::vec4 &color);
	// void setDirectionalLight(glm::vec3 &direction, glm::vec4 &color, float ambientComponent);
	// void setTexture(GLuint texture);
	// void setTexture(GLuint *texture);
	// void setTextureArray(GLuint *texture, int layer);
	
	// void hasVertexPosition(bool value);
	// void hasVertexColor(bool value);
	// void hasVertexNormal(bool value);
	// void hasVertexUV(bool value);
	// void addVertexComponents(std::vector<FAMaterialComponent *> *components);
	
	// bool addMaterialComponent(FAMaterialComponent *component);
	// void setAttribute(std::string name, float value);
	// void create();
	//check requirements
	//add new requirements
	//addThis
	
	void bind();
	void bindShadow();
	void setLightDirection(glm::vec3 &direction);
	void setViewProjectionwMatrix(glm::mat4 &VPMatrix);
	void setModelMatrix(glm::mat4 &modelMatrix);
	void setTexture(GLuint *texture);
	void setInverseShadowMatrix(glm::mat4 *inverseTextureMatrix);
	void setArmature(FAArmature *armature);
};

#endif
