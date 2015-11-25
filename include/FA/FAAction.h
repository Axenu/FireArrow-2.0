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

	virtual void setNode(FANode *node);
	virtual bool update(float dt) = 0;

	virtual ~FAAction();
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

class FAActionRotateBy : public FAAction {

	glm::vec3 rotateBy;

public:
	FAActionRotateBy();
	FAActionRotateBy(glm::vec3 diff, float duration);

	bool update(float dt);

	~FAActionRotateBy();
};

class FAActionRotateTo : public FAAction {

	glm::vec3 rotateToAngle;

public:
	FAActionRotateTo();
	FAActionRotateTo(glm::vec3 angle, float duration);

	bool update(float dt);

	~FAActionRotateTo();
};

class FAActionGroup : public FAAction {

	std::vector<FAAction *> actions;

public:
	FAActionGroup();
	FAActionGroup(std::vector<FAAction *> actions);

	void setNode(FANode *node);
	void addAction(FAAction *action);

	bool update(float dt);

	~FAActionGroup();
};

class FAActionSequence : public FAAction {

	std::vector<FAAction *> actions;

public:
	FAActionSequence();
	FAActionSequence(std::vector<FAAction *> actions);

	void setNode(FANode *node);
	void addAction(FAAction *action);

	bool update(float dt);

	~FAActionSequence();
};

class FAActionRemoveFromParent : public FAAction {

	std::vector<FAAction *> actions;

public:
	FAActionRemoveFromParent();

	bool update(float dt);

	~FAActionRemoveFromParent();
};

#endif