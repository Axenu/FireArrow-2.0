#include <FA/FAScene.h>
#include <FA/FAEngine.h>

FAScene::FAScene() {
	//Default stuff
	defaultPass = new FAMainRenderPass();
    // FARenderPass *shadow = new FACSMRenderPass();
	renderPasses = new FARenderPass*[1];
	renderPasses[0] = defaultPass;
    // renderPasses[0] = shadow;
    defaultPass->setCB(this);
    // shadow->setCB(this);
	this->numberOfPasses = 1;
	this->isActive = true;
	this->childTree = new FAQuadTree(0, FAAABB(glm::vec3(0,0,0), glm::vec3(50,0,50)));
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
    
    camera = new FACamera(40.0f, 640, 480, 0.1, 400);
    
    this->init();
}

void FAScene::onUpdate(float dt) {
    if (!isActive) {
        return;
    }
    rootNode.update(dt);
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
    for (FAGUIElement *element : GUIElements) {
        element->update(dt);
    }
}

void FAScene::onRender() {
	if (!isActive) return;
    camera->useView();
	for (int i = 0; i < numberOfPasses; i++) {
        renderPasses[i]->render();
    }
	// this->render();
    glClear(GL_DEPTH_BUFFER_BIT);
    for (FAGUIElement *element : GUIElements) {
        element->render();
    }
}

void FAScene::addChild(FAGUIElement *child) {
    GUIElements.push_back(child);
}

void FAScene::addChild(FANode *child) {
	rootNode.addChild(child);
	if (FAModel *model = dynamic_cast<FAModel *>(child)) {
        for (FAMaterialComponent *component : requiredComponents) {
            model->addMaterialComponent(component);
        }
		model->getMaterial().setCamera(this->camera);
		childTree->insert(model);
		models.push_back(model);
	} else if (FALight *light = dynamic_cast<FALight *>(child)) {
        lights.push_back(light);
        for (FARenderPass *pass : *light->getRequirements()) {
            addRenderPass(pass);
        }
        for (FAModel *model : models) {
            for (FAMaterialComponent *component : *light->getMaterialRequirements()) {
                model->addMaterialComponent(component);
                requiredComponents.push_back(component);
            }
        }
    } else {
        std::cout << "Added unknown type as child of FAScene" << std::endl;
    }
}

void FAScene::addRenderPass(FARenderPass *renderPass) {
    std::cout << "adding renderPass!" << std::endl;
	this->numberOfPasses++;
    renderPass->setCB(this);
	renderPass->setWindowHeight(this->windowHeigth);
	renderPass->setWindowWidth(this->windowWidth);
	renderPass->finalize();
	FARenderPass **temp = new FARenderPass*[this->numberOfPasses];
	for (int i = 0; i < this->numberOfPasses-1; i++) {
		if (renderPass->getPriority() < renderPasses[i]->getPriority()) {
            temp[i] = renderPass;
            renderPass = renderPasses[i];
        } else {
            temp[i] = renderPasses[i];
        }
	}
	temp[this->numberOfPasses-1] = renderPass;
	delete[] renderPasses;
	renderPasses = temp;
}

void FAScene::setCallback(FAEngine *_callback) {
    this->callback = _callback;
}

void FAScene::setWindowSize(int width, int height) {
    this->windowWidth = width;
	this->windowHeigth = height;
	defaultPass->setWindowWidth(this->windowWidth);
	defaultPass->setWindowHeight(this->windowHeigth);
}

void FAScene::setCursorState(int state) {
    this->callback->setCursorState(state);
}

void FAScene::getMouseKeyInput(int button, int action) {
    //TODO
    // print(lastCursorPosition);
     if (getCursorState() == GLFW_CURSOR_NORMAL) {
			 if (currentElement != nullptr) {
				 if (button == GLFW_MOUSE_BUTTON_1) {
					 if (action == GLFW_PRESS) {
						 currentElement->cursorPress();
                         return;
					 } else {
						 currentElement->cursorRelease();
						 return;
					 }
                 }
         }
	 } else {
		 mouseKeyInput(button, action);
	 }
}

void FAScene::getCursorPosition(double x, double y) {
    // lastCursorPosition = glm::vec2(x/windowWidth,y/windowHeigth);
	lastCursorPosition = glm::vec2(x/windowWidth,y/windowHeigth);
	bool found = false;
	if (getCursorState() == GLFW_CURSOR_NORMAL) {
		for (FAGUIElement *node : GUIElements) {
			FAGUIElement *e = node->testCursorCollition(lastCursorPosition);
			if (e != nullptr) {
				if (currentElement != nullptr) {
					if (e != currentElement) {
						currentElement->cursorLeave();
						e->cursorEnter();
						currentElement = e;
					}
				} else {
					currentElement = e;
					e->cursorEnter();
				}
				found = true;
				break;
			}
		}
		if (!found) {
			if (currentElement != nullptr) {
				currentElement->cursorLeave();
				currentElement = nullptr;
			}
		}
	}
    cursorPosition(x, y);
}

int FAScene::getCursorState() {
    return callback->getCursorState();
}

void FAScene::cullModels(FACamera *cam) {
	culledModels = childTree->cull(cam);
}

std::vector<FAModel *> *FAScene::getModels() {
//	return &this->models;
	//for culling
	return &this->culledModels;
}

FACamera *FAScene::getCamera() {
	return (this->camera);
}

//for culling debugging
FACamera *FAScene::getCullCamera() {
	return this->cullCamera;
}

float FAScene::getWindowWidths() {
    return this->windowWidth;
}

FAScene::~FAScene() {

}