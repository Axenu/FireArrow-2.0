#include <FA/FAAction.h>

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
		this->node->move(this->moveByDistance * remaningDuration);
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
