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

class FAMesh {

private:
	GLint numberOfVertices;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	bool _hasNormal;
	bool _hasColor;

public:
	FAMesh();
	FAMesh(std::string path);

	void render() const;
	
	~FAMesh();
	
};

#endif