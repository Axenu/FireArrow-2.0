#include <FA/FAHUDElement.h>

FAHUDElement::FAHUDElement() {

}

void FAHUDElement::setID(int id) {
	this->identity = id;
}

void FAHUDElement::setPosition(glm::vec3 position) {
	this->position = position;
}

void FAHUDElement::setPosition(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

void FAHUDElement::setX(float x) {
	this->position.x = x;
}

void FAHUDElement::setY(float y) {
	this->position.y = y;
}

void FAHUDElement::setZ(float z) {
	this->position.z = z;
}

void FAHUDElement::setSize(float width, float height) {
	this->width = width;
	this->height = height;
}

void FAHUDElement::setWidth(float width) {
	this->width = width;
}

void FAHUDElement::setHeight(float height) {
	this->height = height;
}

int FAHUDElement::getID() {
	return this->identity;
}

void FAHUDElement::onUpdate(float dt) {
	this->update(dt);
}

void FAHUDElement::onRender() {
	this->render();
}

FAHUDElement::~FAHUDElement() {

}