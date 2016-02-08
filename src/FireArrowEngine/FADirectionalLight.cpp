#include <FA/FADirectionalLight.h>

FADirectionalLight::FADirectionalLight() {
	lightComponent = new FADirectionalLightComponent();
//	lightComponent->setDirection(&this->direction);
	lightComponent->setModelMatrix(&this->modelMatrix);
	lightComponent->setColor(&this->color);
	
	this->materialRequirements.push_back(lightComponent);
	this->renderPass = nullptr;
}

void FADirectionalLight::onUpdate(float dt) {

}

void FADirectionalLight::setDirection(glm::vec3 direction) {
//	this->direction = direction;
//	renderPass->setDirection(direction);
	
//	glm::vec3 v = glm::vec3(0,0,-1);
//	v = glm::normalize(v);
//	
//	float x1 = asinf(v.y);
//	float x2 = glm::pi<float>() - x1;
//	float x3 = acosf(v.z);
//	float x4 = -x3;
//	float f = x1;
//	
//	float d1 = x1 - x3;
//	float d2 = x1 - x4;
//	float d3 = x2 - x3;
//	float d4 = x2 - x4;
//	
//	if (d1 > d2) {
//		d1 = d2;
//	}
//	if (d1 > d3) {
//		d1 = d3;
//		f = x2;
//	}
//	if (d1 > d4) {
//		d1 = d4;
//		f = x2;
//	}
//	this->rotation.x = f;
//	
//	float y1 = asinf(v.x);
//	float y2 = glm::pi<float>() - y1;
//	float y3 = acosf(v.z);
//	float y4 = -y3;
//	f = y1;
//	
//	d1 = y1 - y3;
//	d2 = y1 - y4;
//	d3 = y2 - y3;
//	d4 = y2 - y4;
//	
//	if (d1 > d2) {
//		d1 = d2;
//	}
//	if (d1 > d3) {
//		d1 = d3;
//		f = y2;
//	}
//	if (d1 > d4) {
//		d1 = d4;
//		f = y2;
//	}
//	this->rotation.y = f;
	
//	float r = sqrtf(direction.x*direction.x+direction.y*direction.y+direction.z*direction.z);
	float t = atanf(direction.y/direction.x);
	float p = acosf(direction.z);
	
	this->rotation.x = p;
	if (direction.x == 0) {
		t = 0;
	}
	this->rotation.y = t - glm::pi<float>();

}

void FADirectionalLight::setShadowMap(FAShadowRenderPass &pass) {
	this->renderPass = new FACSMRenderPass();
//	this->renderPass->setDirection(&this->direction);
	this->renderPass->setModelMatrix(&this->modelMatrix);
	lightComponent->setShadow(true);
	// lightComponent->setAmbientComponent(&this->ambient);
//	this->shadowMap = renderPass->getShadowMap();
	for (FAMaterialComponent *c : renderPass->getRequiredMaterialComponents()) {
		this->materialRequirements.push_back(c);
	}
	this->requirements.push_back(renderPass);
}

GLuint *FADirectionalLight::getShadowMap() {
	return shadowMap;
}

FADirectionalLight::~FADirectionalLight() {

}

//enable addition of CSM after child added