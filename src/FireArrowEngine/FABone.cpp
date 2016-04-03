#include <FA/FABone.h>

FABone::FABone() {
	this->children = *new std::vector<FABone *>();
}

FABone::FABone(std::string _name, glm::vec3 _position) {
	this->children = *new std::vector<FABone *>();
	this->name = _name;
	this->position = position;
}

void FABone::addChild(FABone *child) {
	children.push_back(child);
}

void FABone::setParent(FABone *_parent) {
	this->parent = _parent;
	if (parent != NULL) {
		_parent->addChild(this);
	}
}

void FABone::setGlobalPosition(glm::vec3 _position) {
	this->globalPosition = _position;
	this->position = _position;
}

void FABone::setPosition(glm::vec3 _position) {
	this->position = _position;
}

void FABone::setRotation(glm::vec3 _rotation) {
	this->rotation = _rotation;
}

void FABone::setScale(glm::vec3 _scale) {
	this->scale = _scale;
}

void FABone::setName(std::string _name) {
	this->name = _name;
}

void FABone::setLocalMatrix(glm::mat4 matrix) {
	this->localMatrix = matrix;
}

void FABone::setCombinedMatrix(glm::mat4 matrix) {
	this->combinedMatrix = matrix;
}

std::vector<FABone *> FABone::getChildren() {
	return this->children;
}

FABone *FABone::getParent() {
	return this->parent;
}

glm::vec3 FABone::getGlobalPosition() {
	return this->globalPosition;
}

glm::vec3 FABone::getPosition() {
	return this->position;
}

glm::vec3 FABone::getRotation() {
	return this->rotation;
}

glm::vec3 FABone::getScale() {
	return this->scale;
}

std::string FABone::getName() {
	return this->name;
}

glm::mat4 FABone::getLocalMatrix() {
	return this->localMatrix;
}

glm::mat4 FABone::getCombinedMatrix() {
	return this->combinedMatrix;
}

FABone::~FABone() {
	for (FABone *b : children) {
		delete b;
	}
}