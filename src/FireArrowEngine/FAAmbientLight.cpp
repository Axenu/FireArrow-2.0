#include <FA/FAAmbientLight.h>

FAAmbientLight::FAAmbientLight() {
	this->strength = 0.5;
	this->color = glm::vec4(1,1,1,1);
	this->finalColor = color * strength;
	FAAmbientLightComponent *ambientComponent = new FAAmbientLightComponent();
	ambientComponent->setColor(&this->finalColor);
	this->materialRequirements.push_back(ambientComponent);
}

FAAmbientLight::FAAmbientLight(glm::vec4 &color, float strength) {
	this->strength = strength;
	this->color = color;
	this->finalColor = color * strength;
	FAAmbientLightComponent *ambientComponent = new FAAmbientLightComponent();
	ambientComponent->setColor(&this->finalColor);
	this->materialRequirements.push_back(ambientComponent);
}

void FAAmbientLight::onUpdate(float dt) {

}

void FAAmbientLight::setColor(glm::vec4 &color) {
	this->color = color;
}

FAAmbientLight::~FAAmbientLight() {

}