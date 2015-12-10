#include <FA/FAPointLight.h>

FAPointLight::FAPointLight() {
	// renderPass = new FACSMRenderPass();
	FADiffuseLightComponent *lightComponent = new FADiffuseLightComponent();
	lightComponent->setPosition(&this->position);
	lightComponent->setColor(&this->color);
	lightComponent->setRadius(&this->radius);
	// lightComponent->setShadow(true);
	// lightComponent->setAmbientComponent(&this->ambient);
	// FACSMComponent *csmComponent = new FACSMComponent();
	// csmComponent->setTexture(renderPass->getShadowMap());
	// csmComponent->setFrustums(renderPass->getFrustums());
	// csmComponent->setInverseShadowMatrix(renderPass->getInverseShadowMatrix());
	// this->requirements.push_back(renderPass);
	this->materialRequirements.push_back(lightComponent);
	// this->materialRequirements.push_back(csmComponent);
	// this->shadowMap = renderPass->getShadowMap();
}

void FAPointLight::onUpdate(float dt) {

}

void FAPointLight::setRadius(float radius) {
	this->radius = radius;
}

FAPointLight::~FAPointLight() {

}