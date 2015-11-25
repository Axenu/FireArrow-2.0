#include "testScene.h"

void testScene::init() {
    font = new FAFont("Helvetica.ttf", 20, 640, 480);
    text = new FAGUIText(font);
    text->setText("fps: 0.0");
    text->setPosition(0.01,0.95);
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
    FADirectionalLight *light;
    glm::vec3 direction = glm::vec3(1,0.5,0);

    camera = new FACamera(40.0f, 640, 480, 0.1, 400);
    FAMesh *mesh = new FAMesh("tree.fa");
    FAMaterial *material = new FAMaterial();
    material->addMaterialComponent(new FAVertexColorComponent());
    // material->setDirectionalLight(direction, color, ambient);
    FAModel *m = new FAModel(*mesh, *material);
    m->setPosition(0,0,-5);

    //testing actions
    FAActionSequence *group = new FAActionSequence();
    group->addAction(new FAActionMoveTo(glm::vec3(10,0,-5), 3.0f));
    group->addAction(new FAActionRotateBy(glm::vec3(0,31.4,0), 20.0f));

    m->runAction(group);
    addChild(m);
    m = new FAModel(*mesh, *material);
    m->setPosition(10,0,1);
    addChild(m);
    m = new FAModel(*mesh, *material);
    addChild(m);
    FATerrain *t = new FATerrain();
    // t->setMaterial(material);
    addChild(t);

    light = new FADirectionalLight();
    light->setColor(color);
    light->setDirection(direction);
    // light->setAmbientComponent(ambient);
    addChild(light);

    FAAmbientLight *alight = new FAAmbientLight(color, 0.3f);
    addChild(alight);

    // FAShadowMapRenderPass *pass = new FAShadowMapRenderPass();
    // addRenderPass(pass);
    // FAMaterial *textMaterial = new FAMaterial();
    // FATextureComponent *comp = new FATextureComponent();
    // comp->setTexture(texture);
    // texture = *pass->getShadowMap();
    // textMaterial->setTextureArray(light->getShadowMap(), 0);
    // textMaterial->addMaterialComponent(comp);

}

void testScene::render() {

}

void testScene::update(float dt) {
    
    camera->moveX(cameraMovement.z * dt * sin(camera->getRY()));
    camera->moveZ(-cameraMovement.z * dt * cos(camera->getRY()));
    
    camera->moveX(cameraMovement.x * dt * cos(camera->getRY()));
    camera->moveZ(cameraMovement.x * dt * sin(camera->getRY()));
    camera->moveY(cameraMovement.y * dt);

    text->setText(("fps: " + std::to_string(1/dt)));
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
            camera->setPosition(camera->getPosition());
            camera->setRX(camera->getRX());
            camera->setRY(camera->getRY());
            camera->setRZ(camera->getRZ());
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