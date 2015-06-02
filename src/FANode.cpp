#include "FANode.h"

FANode::FANode() {
	scale = glm::vec3(1,1,1);
}

void FANode::addChild(FANode *child) {
	children.push_back(child);
}

std::vector<FANode *> FANode::getAllChildren() {
	std::vector<FANode *> v;
	for (FANode *child : children) {
		for (FANode *n : child->getAllChildren()) {
			v.push_back(n);
		}
	}
	v.push_back(this);
	return v;
}

void FANode::setX(float x) {
    position.x = x;
}

void FANode::setY(float y) {
    position.y = y;
}

void FANode::setZ(float z) {
    position.z = z;
}

void FANode::setPosition(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void FANode::setPosition(glm::vec3 pos) {
    position = pos;
}

void FANode::moveX(float x) {
    position.x += x;
}

void FANode::moveY(float y) {
    position.y += y;
}

void FANode::moveZ(float z) {
    position.z += z;
}

void FANode::move(glm::vec3 p) {
    position += p;
}

void FANode::setScale(float p) {
    scale = glm::vec3(p,p,p);
}

void FANode::setScale(glm::vec3 p) {
    scale = p;
}

void FANode::setScale(float x, float y) {
    scale.x = x;
    scale.y = y;
}

void FANode::setRX(float rx) {
    rotation.x = rx;
}

void FANode::setRY(float ry) {
    rotation.y = ry;
}

void FANode::setRZ(float rz) {
    rotation.z = rz;
}

void FANode::rotateX(float f) {
    rotation.x += f;
}

void FANode::rotateY(float f) {
    rotation.y += f;
}

void FANode::rotateZ(float f) {
    rotation.z += f;
}

float FANode::getX()  {
    return position.x;
}

float FANode::getY()  {
    return position.y;
}

float FANode::getZ()  {
    return position.z;
}

float FANode::getRX()  {
    return rotation.x;
}

float FANode::getRY()  {
    return rotation.y;
}

float FANode::getRZ()  {
    return rotation.z;
}

glm::vec3 FANode::getScale()  {
    return scale;
}

glm::vec3 FANode::getPosition()  {
    return position;
}

glm::vec3 FANode::getRotation()  {
    return rotation;
}

FANode::~FANode() {
	
}