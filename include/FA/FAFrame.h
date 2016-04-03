#ifndef __First__FAFrame__
#define __First__FAFrame__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class FAFrame {
	
	int numberOfBones;
	int index;
	glm::quat *boneRotations;
	
public:
	
	FAFrame();
	FAFrame(int numberOfBones);
	
	void addQuaternion(glm::quat &quat);
	glm::quat &getQuaternionOfBone(int bone);
	
	~FAFrame();
	
};

#endif