#include "testScene.h"

void testScene::init() {
	
	FAFont *n = new FAFont("Arial");
	
    font = new FAFont("Helvetica.ttf", 20, 640, 480);
    text = new FAGUILabel(n);
    text->setText("fps: 0.0");
    text->setPosition(0,0);
    addChild(text);

    // FAGUIMaterialComponent *comp = new FAGUIMaterialComponent();
    // comp->setPosition(0.5,0.5);
    // addChild(comp);
    // FAMaterial *material = new FAMaterial();
    // material->addMaterialComponent(new FAVertexColorComponent());
    // FAMesh *mesh = new FAMesh("barrel.fa");
    // FAModel *model = new FAModel(*mesh, *material);
    // this->addChild(model);


    glm::vec4 color = glm::vec4(1,1,1,1);
    // float ambient = 0.5;
//    FADirectionalLight *light;
	// FACSMRenderPass *pass = new FACSMRenderPass();
	direction = glm::vec3(1,1,1);

    camera = new FACamera(40.0f, 640, 480, 0.1, 400);
    FAMesh *mesh = new FAMesh("tree.fa");
    FACSMRenderPass *pass = new FACSMRenderPass();
    pass->setDirection(&direction);
    this->addRenderPass(pass);

    Material *ma = new Material();
	ma->setLightDirection(direction);
    ma->setTexture(pass->getShadowMap());
    ma->setInverseShadowMatrix(pass->getInverseShadowMatrix());
    FAModel *m = new FAModel(mesh, ma);
    m->setPosition(0,0,-5);
	

    addChild(m);
    m = new FAModel(mesh, ma);
    m->setPosition(10,0,0);
    addChild(m);
    m = new FAModel(mesh, ma);
    addChild(m);
    FATerrain *t = new FATerrain();
    // t->setMaterial(material);
    addChild(t);


//    FAGUITexturedPlane *plane = new FAGUITexturedPlane(pass->getShadowMap());
//    plane->setHeight(0.5);
//    plane->setWidth(0.5);
//    plane->setPosition(0,0);
//    addChild(plane);

	SkinningMaterial *materialS = new SkinningMaterial();
	materialS->setLightDirection(direction);
	materialS->setTexture(pass->getShadowMap());
	materialS->setInverseShadowMatrix(pass->getInverseShadowMatrix());
	animated = new FAMesh("animatedblend.fa");
	materialS->setArmature(animated->getArmature());
	FAModel *anim = new FAModel(animated, materialS);
	this->addChild(anim);
	
	this->getMainPass()->enablePostProcessing();
	
	FAGaussianRenderPass *gp = new FAGaussianRenderPass();
	gp->setRenderdTexture(this->getMainPass()->getFBOTexture());
	
	this->addRenderPass(gp);
	
	
	// FAMesh *sphere = new FAMesh("sphere.fa");
	// FAModel *sp = new FAModel(*sphere, *material);
	
	// for (FABone *b : animated->bones) {
	// 	sp = new FAModel(*sphere, *material);
	// 	sp->setPosition(b->getGlobalPosition());
	// 	addChild(sp);
	// }

//    FAPointLight *pLight = new FAPointLight();
//	glm::vec4 redColor = glm::vec4(1,0,0,1);
//    pLight->setColor(redColor);
//    pLight->setPosition(0,1,0);
//    addChild(pLight);
//	pLight->runAction(group);

    // FAShadowMapRenderPass *pass = new FAShadowMapRenderPass();
    // addRenderPass(pass);
    // FAMaterial *textMaterial = new FAMaterial();
    // FATextureComponent *comp = new FATextureComponent();
    // comp->setTexture(texture);
    // texture = *pass->getShadowMap();
    // textMaterial->setTextureArray(light->getShadowMap(), 0);
    // textMaterial->addMaterialComponent(comp);
	
//	FAFont *lightFont = new FAFont("helveticaneue-light-webfont.ttf", 20, this->windowWidth, this->windowHeigth);

	// FAGUIMenu *menu = new FAGUIMenu(n);
	// menu->addLabel("test Label");
	// menu->addLabel("Hello gWorld!");
	// menu->addLabel("test Label");
	// menu->addLabel("Hello gWorld!");
	// menu->addLabel("test Label");
	// menu->addLabel("Hello gWorld!");
	// menu->addUpdatedLabel("camX", &(camera->position.x), 5);
	// this->addChild(menu);
	
//	FAGUIButton *b1 = new FAGUIButton(n);
//	b1->setText("Add");
//	this->addChild(b1);
//	std::cout << text->getWidth() << std::endl;
	
	// FAGUIPlane *p1 = new FAGUIPlane();
	// p1->setHeight(0.1);
	// p1->setWidth(0.18);
	// p1->setPosition(0, 0);
	// addChild(p1);
//
//	FAGUIText *t1 = new FAGUIText(lightFont);
//	t1->setY(0.025);
//	t1->setX(0.025);
//	addChild(t1);

}

void testScene::render() {

}

void testScene::update(float dt) {
    
    camera->moveX(cameraMovement.z * dt * sin(camera->getRY()));
    camera->moveZ(-cameraMovement.z * dt * cos(camera->getRY()));
    
    camera->moveX(cameraMovement.x * dt * cos(camera->getRY()));
    camera->moveZ(cameraMovement.x * dt * sin(camera->getRY()));
    camera->moveY(cameraMovement.y * dt);

    if (time < 0.2) {
        time += dt;
        frames++;
    } else {
        text->setText(("fps: " + std::to_string(frames/0.2)));
        time -= 0.2;
        frames = 0;
    }
}

void testScene::buttonPressed(int index) {
    
}

void testScene::getKeyInput(int key, int action) {
    
    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS) {
            cameraMovement.z += speed;
        } else if (action == GLFW_RELEASE) {
            cameraMovement.z -= speed;
        }
    } else if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            cameraMovement.z -= speed;
        } else if (action == GLFW_RELEASE) {
            cameraMovement.z += speed;
        }
    } else if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            cameraMovement.x += speed;
        } else if (action == GLFW_RELEASE) {
            cameraMovement.x -= speed;
        }
    } else if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            cameraMovement.x -= speed;
        } else if (action == GLFW_RELEASE) {
            cameraMovement.x += speed;
        }
    } else if (key == GLFW_KEY_SPACE) {
        if (action == GLFW_PRESS) {
            cameraMovement.y += speed;
        } else if (action == GLFW_RELEASE) {
            cameraMovement.y -= speed;
        }
    } else if (key == GLFW_KEY_LEFT_SHIFT) {
        if (action == GLFW_PRESS) {
            cameraMovement.y -= speed;
        } else if (action == GLFW_RELEASE) {
            cameraMovement.y += speed;
        }
    } else if (key == GLFW_KEY_E) {
        if (action == GLFW_PRESS) {
//            camera->setPosition(camera->getPosition());
//            camera->setRX(camera->getRX());
//            camera->setRY(camera->getRY());
//            camera->setRZ(camera->getRZ());
        } else if (action == GLFW_RELEASE) {
        }
    } else if (key == GLFW_KEY_ESCAPE) {
        if (action == GLFW_PRESS) {
            if (getCursorState() == GLFW_CURSOR_DISABLED) {
                setCursorState(GLFW_CURSOR_NORMAL);
            } else {
                setCursorState(GLFW_CURSOR_DISABLED);
            }
        }
    } else {
        std::cout << "Key: " << key << " action: " << action << std::endl;
    }
}

void testScene::mouseKeyInput(int button, int action) {
    
}

void testScene::cursorPosition(double x, double y) {
        //calculated from the uppear left corner
        glm::vec2 currentCursorPos = glm::vec2(x, y);
        glm::vec2 deltaCursorPos = currentCursorPos - previousCursorPosition;
        previousCursorPosition = currentCursorPos;
        if (!cursorHasMoved) {
            if (previousCursorPosition != glm::vec2()) {
                cursorHasMoved = true;
                return;
            }
        }
        if (getCursorState() == GLFW_CURSOR_DISABLED) {
            camera->rotateY(deltaCursorPos.x / 1000.0f);
            camera->rotateX(deltaCursorPos.y / 1000.0f);
        }
}