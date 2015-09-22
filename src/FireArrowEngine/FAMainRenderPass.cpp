#include <FA/FAMainRenderPass.h>

FAMainRenderPass::FAMainRenderPass() {

    this->priority = 0;
    this->name = "Main";
}


void FAMainRenderPass::render() {
	// std::cout << "renderMain" << std::endl;
	glClearColor(0.5,0,0,1);
	if (parent != nullptr) {
		// std::vector<FAModel *> *mo = parent->getModels();
		// glm::mat4 &m = parent->getWindowWidth() << std::endl;
		// std::cout << parent->getModels()->size() << std::endl;
		for (FAModel *m : *parent->getModels()) {
			m->getMaterial().setViewProjectionwMatrix(&(parent->getCamera()->VPMatrix));
			// m->getMaterial().setModelMatrix(m->modelMatrix);
			m->getMaterial().bind();
			m->getMesh().render();
		}
	}
}