#include <FA/FAAction.h>

//idea for upgrade:
// @ multiple funktions for linear, exponentionl, and sinus movement
// @ adding support for GUIElements

FAAction::FAAction() {

}

void FAAction::setNode(FANode *node) {
	this->node = node;
}

FAAction::~FAAction() {

}

FAActionMoveBy::FAActionMoveBy() {
	this->moveByDistance = glm::vec3();
	this->duration = 0.0f;
	this->remaningDuration = 0.0f;
}

FAActionMoveBy::FAActionMoveBy(glm::vec3 diff, float duration) {
	this->moveByDistance = diff;
	this->duration = duration;
	this->remaningDuration = duration;
}

bool FAActionMoveBy::update(float dt) {
	float diff = (dt/this->duration);
	if (this->remaningDuration - dt < 0) {
		diff = (this->remaningDuration/this->duration);
		this->node->move(this->moveByDistance * diff);
		return false;
	} else {
		this->node->move(this->moveByDistance * diff);
	}
	this->remaningDuration -= dt;
	return true;
}

FAActionMoveBy::~FAActionMoveBy() {

}

FAActionMoveTo::FAActionMoveTo() {
	this->moveToPoint = glm::vec3();
	this->duration = 0.0f;
	this->remaningDuration = 0.0f;
}

FAActionMoveTo::FAActionMoveTo(glm::vec3 point, float duration) {
	this->moveToPoint = point;
	this->duration = duration;
	this->remaningDuration = duration;
}

bool FAActionMoveTo::update(float dt) {
	float diff = (dt/this->remaningDuration);
	if (this->remaningDuration - dt < 0) {
		this->node->setPosition(moveToPoint);
		return false;
	} else {
		glm::vec3 remaningDistance = this->moveToPoint - this->node->getPosition();
		this->node->move(remaningDistance * diff);
	}
	this->remaningDuration -= dt;
	return true;
}

FAActionMoveTo::~FAActionMoveTo() {
}

FAActionRotateBy::FAActionRotateBy() {
	this->rotateBy = glm::vec3();
	this->duration = 0.0f;
	this->remaningDuration = 0.0f;
}

FAActionRotateBy::FAActionRotateBy(glm::vec3 diff, float duration) {
	this->rotateBy = diff;
	this->duration = duration;
	this->remaningDuration = duration;
}

bool FAActionRotateBy::update(float dt) {
	float diff = (dt/this->duration);
	if (this->remaningDuration - dt < 0) {
		diff = (this->remaningDuration/this->duration);
		this->node->rotate(this->rotateBy * diff);
		return false;
	} else {
		this->node->rotate(this->rotateBy * diff);
	}
	this->remaningDuration -= dt;
	return true;
}

FAActionRotateBy::~FAActionRotateBy() {

}

FAActionRotateTo::FAActionRotateTo() {
	this->rotateToAngle = glm::vec3();
	this->duration = 0.0f;
	this->remaningDuration = 0.0f;
}

FAActionRotateTo::FAActionRotateTo(glm::vec3 angle, float duration) {
	this->rotateToAngle = angle;
	this->duration = duration;
	this->remaningDuration = duration;
}

bool FAActionRotateTo::update(float dt) {
	float diff = (dt/this->remaningDuration);
	if (this->remaningDuration - dt < 0) {
		this->node->setPosition(rotateToAngle);
		return false;
	} else {
		glm::vec3 remaningDistance = this->rotateToAngle - this->node->getRotation();
		this->node->rotate(remaningDistance * diff);
	}
	this->remaningDuration -= dt;
	return true;
}

FAActionRotateTo::~FAActionRotateTo() {
}

FAActionGroup::FAActionGroup() {

}

FAActionGroup::FAActionGroup(std::vector<FAAction *> actions) {
	this->actions = actions;
}

void FAActionGroup::setNode(FANode *node) {
	this->node = node;
	for (FAAction *a : this->actions) {
		a->setNode(this->node);
	}
}

void FAActionGroup::addAction(FAAction *action) {
	this->actions.push_back(action);
}

bool FAActionGroup::update(float dt) {
	FAAction *a = nullptr;
	for (int i = 0; i < actions.size(); i++) {
		a = actions[i];
		if (a != nullptr) {
			if (!a->update(dt)) {
				delete a;
				actions.erase(actions.begin()+i);
				i--;
			}
		}
	}
	if (actions.size() < 1) {
		return false;
	}
	return true;
}

FAActionGroup::~FAActionGroup() {
	for (FAAction *a : this->actions) {
		delete a;
	}
	actions.clear();
}

FAActionSequence::FAActionSequence() {

}

FAActionSequence::FAActionSequence(std::vector<FAAction *> actions) {
	this->actions = actions;
}

void FAActionSequence::setNode(FANode *node) {
	this->node = node;
	for (FAAction *a : this->actions) {
		a->setNode(this->node);
	}
}

void FAActionSequence::addAction(FAAction *action) {
	this->actions.push_back(action);
}

bool FAActionSequence::update(float dt) {
	FAAction *a = nullptr;

	if (actions.size() > 0) {
		a = actions[0];
		if (!a->update(dt)) {
			delete a;
			actions.erase(actions.begin());
		}
	}
	if (actions.size() < 1) {
		return false;
	}
	return true;
}

FAActionSequence::~FAActionSequence() {
	for (FAAction *a : this->actions) {
		delete a;
	}
	actions.clear();
}


