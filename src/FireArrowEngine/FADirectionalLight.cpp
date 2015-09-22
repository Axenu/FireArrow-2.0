#include <FA/FADirectionalLight.h>

FADirectionalLight::FADirectionalLight() {
	FACSMRenderPass *renderPass = new FACSMRenderPass();
	FADirectionalLightComponent *lightComponent = new FADirectionalLightComponent();
	lightComponent->setDirection(&this->direction);
	lightComponent->setColor(&this->color);
	lightComponent->setAmbientComponent(&this->ambient);
	FACSMComponent *csmComponent = new FACSMComponent();
	csmComponent->setTexture(renderPass->getShadowMap());
	csmComponent->setFrustums(renderPass->getFrustums());
	csmComponent->setInverseShadowMatrix(renderPass->getInverseShadowMatrix());
	this->requirements.push_back(renderPass);
	this->materialRequirements.push_back(lightComponent);
	this->materialRequirements.push_back(csmComponent);
	this->shadowMap = renderPass->getShadowMap();
}

void FADirectionalLight::onUpdate(float dt) {

}

void FADirectionalLight::setColor(glm::vec4 &color) {
	this->color = color;
}

void FADirectionalLight::setDirection(glm::vec3 direction) {
	this->direction = direction;
}

void FADirectionalLight::setAmbientComponent(float ambientComponent) {
	this->ambient = ambientComponent;
}

GLuint *FADirectionalLight::getShadowMap() {
	return shadowMap;
}

FADirectionalLight::~FADirectionalLight() {

}