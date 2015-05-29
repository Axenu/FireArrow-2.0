#include "FANode.h"

FANode::FANode() {
	x = 0;
	y = 0;
	z = 0;
}

void FANode::setPosition(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
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

FANode::~FANode() {
	
}