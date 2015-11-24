#ifndef __First__FAAction__
#define __First__FAAction__

#include "FANode.h"

class FANode;

class FAAction {

protected:
	FANode *node;
	float duration;
	float remaningDuration;

public:
	FAAction();

	void setNode(FANode *node);
	virtual bool update(float dt) = 0;

	~FAAction();
	
};

class FAActionMoveBy : public FAAction {

	glm::vec3 moveByDistance;

public:
	FAActionMoveBy();
	FAActionMoveBy(glm::vec3 diff, float duration);

	bool update(float dt);

	~FAActionMoveBy();
	
};

class FAActionMoveTo : public FAAction {

	glm::vec3 moveToPoint;

public:
	FAActionMoveTo();
	FAActionMoveTo(glm::vec3 point, float duration);

	bool update(float dt);

	~FAActionMoveTo();
	
};

#endif