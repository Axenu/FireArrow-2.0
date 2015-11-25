#include <FA/FANode.h>
#include <iostream>

FANode::FANode() {
	scale = glm::vec3(1,1,1);
    position = glm::vec3(0,0,0);
    rotation = glm::vec3(0,0,0);
    this->isActive = true;
    this->modelMatrix = glm::mat4();
}

void FANode::addChild(FANode *child) {
	children.push_back(child);
    child->setParent(this);
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

void FANode::setParent(FANode *parent) {
    this->parent = parent;
}

void FANode::removeFromParent() {
    if (this->parent != nullptr) {
        this->parent->removeChild(this);
    }
}

void FANode::removeChild(FANode *node) {
    FANode *n = nullptr;
    for (int i = 0; i < children.size(); i++) {
        n = children[i];
        if (n == node) {
            delete n;
            children.erase(children.begin()+i);
            return;
        }
    }
}

void FANode::update(float dt) {
    if (!isActive) return;
    this->modelMatrix = glm::translate(glm::mat4(), this->position);
    this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.x, glm::vec3(1,0,0));
    this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.y, glm::vec3(0,1,0));
    this->modelMatrix = glm::rotate(this->modelMatrix, this->rotation.z, glm::vec3(0,0,1));
    this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
    if (this->parent != nullptr) {
        this->modelMatrix = this->parent->modelMatrix * this->modelMatrix;
    }
    if (this->action != nullptr) {
        if (!this->action->update(dt)) {
            delete this->action;
            this->action = nullptr;
        }
    }
    onUpdate(dt);
    for (FANode *node : children)
        node->update(dt);
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

void FANode::rotate(glm::vec3 r) {
    rotation.x += r.x;
    rotation.y += r.y;
    rotation.z += r.z;

    while (rotation.x > M_2PI) rotation.x -= M_2PI;
    while (rotation.y > M_2PI) rotation.y -= M_2PI;
    while (rotation.z > M_2PI) rotation.z -= M_2PI;

    while (rotation.x < 0) rotation.x += M_2PI;
    while (rotation.y < 0) rotation.y += M_2PI;
    while (rotation.z < 0) rotation.z += M_2PI;
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

void FANode::runAction(FAAction *action) {
    this->action = action;
    this->action->setNode(this);
}

FANode::~FANode() {
	
}