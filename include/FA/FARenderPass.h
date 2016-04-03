#ifndef __First__FARenderPass__
#define __First__FARenderPass__

#define GLM_FORCE_RADIANS
#define GLFW_INCLUDE_GLCOREARB

#include <OpenGL/opengl.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "FARenderPasscallbackInterface.h"
// #include "FAScene.h"

// class FAScene;

class FARenderPass {

private:

public:
	FARenderPass();
	virtual ~FARenderPass();

	int getPriority();
	std::string &getName();
	// void setParent(FAScene *parent);

	virtual void render() = 0;
	
	virtual void finalize() {}
	
	void setWindowHeight(int height);
	void setWindowWidth(int width);

	//test callback
	void setCB(FARenderPasscallbackInterface *cb);
	FARenderPasscallbackInterface *parent = nullptr;

protected:
	
	// FAScene *parent;
	int priority;
	int windowWidth;
	int windowHeight;
	std::string name;
};

#endif