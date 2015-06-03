#ifndef __First__FAShader__
#define __First__FAShader__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

class FAShader {

private:
	std::string name;
	GLint createShader(std::string path, GLenum shaderType) const;
	GLint createShaderFromString(std::string *shader, GLenum shaderType) const;
public:

	GLint shaderProgram;
	
	FAShader();
	FAShader(std::string file);
	FAShader(std::string vert, std::string frag);
	FAShader(std::string *vertexShader, std::string *fragmentShader);
	~FAShader();
};

#endif