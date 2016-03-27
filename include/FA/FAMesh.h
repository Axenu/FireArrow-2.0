#ifndef __First__FAMesh__
#define __First__FAMesh__

#define GLFW_INCLUDE_GLCOREARB
#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include "FAArmature.h"
#include "FAMAterialComponent.h"

class FAMesh {

private:

	bool _hasNormal;
	bool _hasColor;
	bool _hasUV;
	bool _hasWeights;
	bool _hasArmature;
	
	std::string objMaterailLib;
	std::string objMaterial;

	std::vector<FAMaterialComponent *> avaliableVertexComponents;

	// FABone *rootBone;
	
	// std::vector<glm::mat4> invBindPose;
	// std::vector<FAAnimation *> animations;
	FAArmature *armature;
	
	void loadOBJModel(std::string path);
	void loadFAModel(std::string path);
	void loadNewFAModel(std::string path);

	// void adjustPositions(FABone *b, glm::vec3 diff);
	// void setupBoneMatrices(FABone *b);
	// int calculateBoneMatrices(FABone *b, int i);

	//list avaliable material thins

public:
	FAMesh();
	FAMesh(std::string path);
	FAMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, bool hasNormal, bool hasColor);

	void render() const;
	void update(float dt);
	
	std::string getOBJMaterialLib();
	std::string getOBJMaterial();
	
	// bool hasVertexPosition();
	// bool hasVertexNormal();
	// bool hasVertexColor();
	// bool hasVertexUV();

	std::vector<FAMaterialComponent *>* getAvaliableComponents();
	FAArmature *getArmature();

	~FAMesh();
	// std::vector<glm::mat4> animatedXForm;
	// std::vector<FABone *> bones;
protected:
	GLint numberOfVertices;
	
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	
};

#endif