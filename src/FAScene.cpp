#include "FAScene.h"
#include "FAEngine.h"

FAScene::FAScene() {
	//Default stuff
	FARenderPass *defaultPass = new FARenderPass();
	renderPasses = new FARenderPass*[1];
	renderPasses[0] = defaultPass;
	defaultPass->setParent(this);
	this->numberOfPasses = 1;
	this->isActive = true;
	// this->models = new std::vector<FAModel *>();
	//User stuff
}

// void FAScene::render() {
	// for (int i = 0; i < numberOfPasses; i++) {
	// 	renderPasses[i]->render();
	// }
// 	// m->render(camera);
// }

void FAScene::onInit() {
    
    // displayFps = true;
    // children = new FANode();
    // camera = new FACamera();
    
    // font = new FAFont("Helvetica.ttf", 15, windowWidth, windowHeigth);
    // fpsText = new FAText2D(font);
    // fpsText->setShader(shaders->getShader("Text2D"));
    // fpsText->setText("fps: 60");
    // fpsText->setPos(glm::vec3(-0.99,0.95,0));
    // fpsText->setColor(FAColorWhite);
    // addHUDElement(fpsText);
    
    // vertexCountText = new FAText2D(font);
    // vertexCountText->setShader(shaders->getShader("Text2D"));
    // vertexCountText->setText("Vertices: 0");
    // vertexCountText->setPos(glm::vec3(-0.99,0.9,0));
    // vertexCountText->setColor(FAColorWhite);
    // addHUDElement(vertexCountText);
    
    this->init();
}

void FAScene::onUpdate(float dt) {
    if (!isActive) {
        return;
    }
    // if (displayFps) {
    //     if (time > 1) {
    //         fpsText->setText("fps: " + std::to_string((frames/time)));
    //         frames = 0;
    //         time = 0;
    //     } else {
    //         time+=dt;
    //         frames++;
    //     }
    //     vertexCountText->setText("vertices: " + std::to_string(children->getVertexCount()));
    // }
    update(dt);
}

void FAScene::onRender() {
	if (!isActive) return;
    camera->useView();
	for (int i = 0; i < numberOfPasses; i++)
        renderPasses[i]->render();
	this->render();
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

void FAScene::setCallback(FAEngine *_callback) {
    this->callback = _callback;
}

void FAScene::setWindowSize(int width, int height) {
    this->windowWidth = width;
    this->windowHeigth = height;
}

void FAScene::setCursorState(int state) {
    this->callback->setCursorState(state);
}

void FAScene::getMouseKeyInput(int button, int action) {
    //TODO
    // print(lastCursorPosition);
    // if (true) {
        // if (button == GLFW_MOUSE_BUTTON_1) {
        //     if (action == GLFW_PRESS) {
        //         for (FAHUDElement *node : HUDElements) {
        //             if (node->handleClick(lastCursorPosition)) {
        //                 buttonPressed(node);
        //                 return;
        //             }
        //         }
        //     }
        // }
    // }
    mouseKeyInput(button, action);
}

void FAScene::getCursorPosition(double x, double y) {
    // lastCursorPosition = glm::vec2(x/windowWidth,y/windowHeigth);
    cursorPosition(x, y);
}

int FAScene::getCursorState() {
    return callback->getCursorState();
}

std::vector<FAModel *> *FAScene::getModels() {
	return &this->models;
}

FACamera *FAScene::getCamera() {
	return (this->camera);
}

FAScene::~FAScene() {

}