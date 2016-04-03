#ifndef __First__FAAnimation__
#define __First__FAAnimation__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include "FAFrame.h"

class FAAnimation {

private:

	// std::vector<std::vector<glm::vec4>*> *keyframes;

//	glm::quat ***keyframes;
	FAFrame **frames;
	int numberOfFrames;
	int index;
	float timePerFrame;
//	int numberOfBones;
	// int numberOfAnimations;
	
	//animations:
	//frames:
	//bones:
	//quaternions

public:
	FAAnimation();

	FAAnimation(int numberOfFrames);
	
	void addFrame(FAFrame *frame);
	void getDiffAndFrame(float time, float &diff, int &frame);
	glm::quat getQuatAtTime(float diff, int frame, int bone);

	void update(float dt);

	~FAAnimation();
	
};

#endif