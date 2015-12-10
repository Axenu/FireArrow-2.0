#include <FA/FALight.h>

FALight::FALight() {

}

void FALight::onUpdate(float dt) {

}

bool FALight::hasShadow() {
	return this->_hasShadow;
}

std::vector<FARenderPass *> *FALight::getRequirements() {
	return &this->requirements;
}

std::vector<FAMaterialComponent *> *FALight::getMaterialRequirements() {
	return &this->materialRequirements;
}

void FALight::setColor(glm::vec4 &color) {
	this->color = color;
}

FALight::~FALight() {

}