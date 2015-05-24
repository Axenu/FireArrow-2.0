#include "FAScene.h"

void FAScene::render() {

}

void FAScene::update(float dt)  {

}

void FAScene::addChild(FANode *child) {
	rootNode.addChild(child);
	for (FANode *n : child->getAllChildren()) {
		children.push_back(n);
	}
}