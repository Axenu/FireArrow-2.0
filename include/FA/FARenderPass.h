#ifndef __First__FARenderPass__
#define __First__FARenderPass__

#define GLM_FORCE_RADIANS

#include <OpenGL/opengl.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "FAScene.h"

class FAScene;

class FARenderPass {

private:
	FAScene *parent;
	int priority;

public:
	FARenderPass();
	~FARenderPass();

	void render();

	int getPriority();

	void setParent(FAScene *parent);
	
};

#endif