#ifndef __First__FAAnimation__
#define __First__FAAnimation__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

class FAAnimation {

private:

	// std::vector<std::vector<glm::vec4>*> *keyframes;

	glm::quat ***keyframes;
	int numberOfFrames;
	int numberOfBones;
	// int numberOfAnimations;
	
	//animations:
	//frames:
	//bones:
	//quaternions

public:
	FAAnimation();

	FAAnimation(int numberOfFrames, int numberOfBones);
	
	void setQuaternion(int frame, int bone, glm::quat q);

	void update(float dt);

	~FAAnimation();
	
};

#endif