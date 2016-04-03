#ifndef __First__FAArmature__
#define __First__FAArmature__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "FAAnimation.h"
#include "FABone.h"

class FAArmature {

private:
	std::vector<FAAnimation *> animations;
	std::vector<FABone *> bones;
	FABone *rootBone;

	std::vector<glm::mat4> invBindPose;
	std::vector<glm::mat4> animatedXForm;
	
	FAAnimation *activeAnimation;
	float animationDuration;

public:
	FAArmature();

	void setRootBone(FABone *bone);
	void addBone(FABone *bone);
	FABone* getBone(int index);
	FABone* getRootBone();
	int getNumberOfBones();
	float* getAnimatedXForm();
	
	void addAnimation(FAAnimation *animation);
	void runAnimation(int index);

	void adjustPositions(FABone *b, glm::vec3 diff);
	void setupBoneMatrices(FABone *b);
	int calculateBoneMatrices(FABone *b, int i);
	int calculateBoneMatricesFromQuaternions(FABone *b, int i);

	void update(float dt);

	~FAArmature();
	
};

#endif