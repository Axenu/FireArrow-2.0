#include "testScene.h"
//
//std::string cftoc(CFStringRef r) {
//    const CFIndex kCStringSize = 128;
//    char temporaryCString[kCStringSize];
//    bzero(temporaryCString,kCStringSize);
//    CFStringGetCString(r, temporaryCString, kCStringSize, kCFStringEncodingUTF8);
//    std::string *bar = new std::string(temporaryCString);
//    return *bar;
//}
//
//void myCallBack(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo) {
//    std::string album = cftoc((CFStringRef)CFDictionaryGetValue(userInfo, CFSTR("Album")));
//    std::string artist = cftoc((CFStringRef)CFDictionaryGetValue(userInfo, CFSTR("Artist")));
//    std::string track = cftoc((CFStringRef)CFDictionaryGetValue(userInfo, CFSTR("Name")));
////    std::string durationS = cftoc((CFStringRef)CFDictionaryGetValue(userInfo, CFSTR("Duration")));
////    std::string currentTimeS = cftoc((CFStringRef)CFDictionaryGetValue(userInfo, CFSTR("Playback Position")));
//    std::string trackID = cftoc((CFStringRef)CFDictionaryGetValue(userInfo, CFSTR("Track ID")));
//    trackID.erase(0, 14);
//    std::cout << trackID << std::endl;
//}

void testScene::init() {

    // DIR *pdir = NULL;
    // pdir = opendir (".");
    // struct dirent *pent = NULL;

    // while (pent = readdir (pdir)) {
    //     if (pent == NULL) {
    //         std::cout << "\nERROR! pent could not be initialised correctly";
    //     } else {
    //         std::cout << pent->d_name << std::endl;
    //     }
    // }

    font = new FAFont("Helvetica.ttf", 20, 640, 480);
    text = new FAText(font);
    text->setText("fps: 0.0");
    text->setPosition(0,0.95,0);
    
    camera = new FACamera(40.0f, 640, 480, 0.1, 400);
    FAMesh *mesh = new FAMesh("tree.fa");
    FAModel *m = new FAModel(*mesh);
    m->setPosition(0,0,-5);
    addChild(m);
    // m = new FAModel(*mesh);
    // m->setPosition(10,1,1);
    // addChild(m);
    // m = new FAModel(*mesh);
    // addChild(m);
    // m = new FAModel(*mesh);
    // addChild(m);

    // camera = new FACamera(40.0f, (float)windowWidth, windowHeigth, 0.001, 400);
    // camera->setZ(0);
    // camera->setY(0);
    // camera->setX(0);
    
    // FAModel *m = new FAModel();
    // m->setShader(new FAShader("FA"));
    // m->setFAModel("barrel.fa");
    // m->setScale(1);
    // m->setPos(glm::vec3(0,0,0));
    // m->setScale(glm::vec3(1,1,1));
    // addChild(m);
    
//    FAMaterial *mat = new FAMaterial();
//    mat->setColor(glm::vec4(1,0,0,1));
//    mat->setGlobalLight();
//    mat->init();
//    m->setMaterial(mat);
//    CFNotificationCenterRef distCenter;
//    CFStringRef evtName = CFSTR("com.spotify.client.PlaybackStateChanged");
//    distCenter = CFNotificationCenterGetDistributedCenter();
//    CFNotificationCenterAddObserver(distCenter, NULL, &myCallBack, evtName, NULL, CFNotificationSuspensionBehaviorDeliverImmediately);
//    CFRunLoopRun();
//    
//    albumArt = new FATexturedPlane2D();
//    albumArt->setShader(shaders->getShader("TexturedPlane2D"));
//    albumArt->setScale(1);
//    albumArt->update(0);
//    albumArt->setTexture(FATexture::createTexture("/Users/Axenu/Documents/Geektool/Spotify/DefaultArtwork/DefaultArtwork.tiff"));
//    addHUDElement(albumArt);
    glEnable(GL_CULL_FACE);
    setCursorState(GLFW_CURSOR_DISABLED);
}

void testScene::render() {
    text->render();
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