#ifndef __First__FAMesh__
#define __First__FAMesh__

#define GLFW_INCLUDE_GLCOREARB
#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h> 

class FAMesh {

private:
	GLint numberOfVertices;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	bool _hasNormal;
	bool _hasColor;
	bool _hasUV;
	bool _hasPosition;

	void loadFAModel(std::string path);
	void loadNewFAModel(std::string path);

public:
	FAMesh();
	FAMesh(std::string path);
	FAMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, bool hasNormal, bool hasColor);

	void render() const;
	
	bool hasVertexPosition();
	bool hasVertexNormal();
	bool hasVertexColor();
	bool hasVertexUV();

	~FAMesh();
	
};

#endif