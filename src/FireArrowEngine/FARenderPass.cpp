#include <FA/FARenderPass.h>

FARenderPass::FARenderPass() {

}

// void FARenderPass::render() {
// 	glClearColor(0.5,0,0,1);
// 	// std::vector<FAModel *> *mo = parent->getModels();
// 	for (FAModel *m : *parent->getModels()) {
// 		m->getMaterial().setViewProjectionwMatrix(&(parent->getCamera()->VPMatrix));
// 		// m->getMaterial().setModelMatrix(m->modelMatrix);
// 		m->getMaterial().bind();
// 		m->getMesh().render();
// 	}
// }

int FARenderPass::getPriority() {
	return this->priority;
}

std::string &FARenderPass::getName() {
	return this->name;
}

void FARenderPass::setCB(FARenderPasscallbackInterface *cb) {
	this->parent = cb;
}

// void FARenderPass::setParent(FAScene *parent) {
// 	this->parent = parent;
// }

FARenderPass::~FARenderPass() {

}