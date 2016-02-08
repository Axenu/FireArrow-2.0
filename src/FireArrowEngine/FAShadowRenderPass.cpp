#include <FA/FAShadowRenderPass.h>

void FAShadowRenderPass::setDirection(glm::vec3 *direction) {
	this->direction = direction;
}

void FAShadowRenderPass::setModelMatrix(glm::mat4 *modelmatrix) {
	this->modelmatrix = modelmatrix;
}

std::vector<FAMaterialComponent *> FAShadowRenderPass::getRequiredMaterialComponents() {
	return this->requiredMaterialComponents;
}