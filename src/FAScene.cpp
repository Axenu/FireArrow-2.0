#include "FAScene.h"

FAScene::FAScene() {
	//Default stuff
	FARenderPass *defaultPass = new FARenderPass();
	renderPasses = new FARenderPass*[1];
	renderPasses[0] = defaultPass;
	defaultPass->setParent(this);
	this->numberOfPasses = 1;
	// this->models = new std::vector<FAModel *>();
	//User stuff

	camera = new FACamera(40.0f, 640, 480, 0.1, 400);
    FAMesh *mesh = new FAMesh("/Users/Axenu/Developer/clang++/first/resources/models/barrel.fa");
    m = new FAModel(*mesh);
    addChild(m);
}

void FAScene::render() {
	for (int i = 0; i < numberOfPasses; i++) {
		renderPasses[i]->render();
	}
	// m->render(camera);
}

void FAScene::update(float dt)  {

}

void FAScene::addChild(FANode *child) {
	rootNode.addChild(child);
	if (dynamic_cast<FAModel *>(child)) {
		models.push_back(dynamic_cast<FAModel *>(child));
		// for (FANode *n : child->getAllChildren()) {
		// 	children.push_back(n);
		// }
	}
}

void FAScene::addRenderPass(FARenderPass *renderPass) {
	this->numberOfPasses++;
	renderPass->setParent(this);
	FARenderPass **temp = new FARenderPass*[this->numberOfPasses];
	int place;
	for (int i = 0; i < this->numberOfPasses-1; i++) {
		if (temp[i]->getPriority() < renderPass->getPriority()) {
			temp[i] = this->renderPasses[i];
		} else {
			i = this->numberOfPasses;
			place = i;
		}
	}
	temp[place] = renderPass;
	for (int i = place+1; i < this->numberOfPasses; i++){
		temp[i] = this->renderPasses[i-1];
	}
	delete[] renderPasses;
	renderPasses = temp;
}

std::vector<FAModel *> *FAScene::getModels() {
	return &this->models;
}

// FACamera &FAScene::getCamera() {
// 	return *(this->camera);
// }

FAScene::~FAScene() {

}