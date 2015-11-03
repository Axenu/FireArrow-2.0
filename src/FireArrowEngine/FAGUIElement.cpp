#include <FA/FAGUIElement.h>

FAGUIElement::FAGUIElement() {

}

void FAGUIElement::addChild(FAGUIElement *child) {
	this->children.push_back(child);
}

void FAGUIElement::update(float dt) {
	this->globalTransformation = glm::vec2(this->position.x, this->position.y);
	onUpdate(dt);
	for (FAGUIElement *child : children)
        child->update(dt, globalTransformation);
}

void FAGUIElement::update(float dt, glm::vec2 transformation) {
	this->globalTransformation = glm::vec2(this->position.x + transformation.x, this->position.y + transformation.y);
	onUpdate(dt);
	for (FAGUIElement *child : children)
        child->update(dt, globalTransformation);
}

void FAGUIElement::render() {
	onRender();
    for (FAGUIElement *child : children)
        child->render();
}

//setters

void FAGUIElement::setID(int id) {
	this->identity = id;
}

void FAGUIElement::setX(float x) {
	this->position.x = x;
}
void FAGUIElement::setY(float y) {
	this->position.y = y;
}
void FAGUIElement::setPosition(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}
void FAGUIElement::setPosition(glm::vec2 pos) {
	this->position = pos;
}
void FAGUIElement::moveX(float x) {
	this->position.x += x;
}
void FAGUIElement::moveY(float y) {
	this->position.y += y;
}
void FAGUIElement::move(glm::vec2 p) {
	this->position += p;
}
void FAGUIElement::setSize(float p) {
	this->size.x = p;
	this->size.y = p;
}
void FAGUIElement::setSize(glm::vec2 p) {
	this->size = p;
}
void FAGUIElement::setSize(float x, float y) {
	this->size.x = x;
	this->size.y = y;
}
void FAGUIElement::setWidth(float width) {
	this->size.x = width;
}
void FAGUIElement::setHeight(float height) {
	this->size.y = height;
}



int FAGUIElement::getID() {
	return this->identity;
}

FAGUIElement::~FAGUIElement() {

}