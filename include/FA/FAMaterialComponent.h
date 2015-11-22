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
	// std::string getVertexIO();
	// std::string getVertexMain();
	// std::string getFragmentIO();
	// std::string getFragmentMain();
	// std::string getFragmentMainOutput();
	// std::string getName();

	// virtual void setAttribute(std::string name, float value) = 0;
	// virtual void bind() = 0;
	// virtual void setUpLocations(GLint shaderProgram) = 0;

	// std::vector<FAMaterialComponent *> *getRequirements();
	// bool requiresModelData();

	//dictionary for required variables
	//dictionary for avaliable variables //all variables
	//list of required model data
	//can be loaded from file

	std::map<std::string, std::string> requiredComponents;
	std::map<std::string, std::string> avaliableComponents;

protected:

	std::string name;
	// std::string vertexIO;
	// std::string vertexMain;
	// std::string fragmentIO;
	// std::string fragmentMain;
	// std::string fragmentOutput;
	// std::map<std::string, FAMaterialComponent *> requirements;
	// std::vector<FAMaterialComponent *> requirements;
	// bool modelData;
	
};

#endif