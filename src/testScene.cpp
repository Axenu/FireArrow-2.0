#include "testScene.h"

void testScene::init() {
    font = new FAFont("Helvetica.ttf", 20, 640, 480);
    text = new FAGUIText(font);
    text->setText("fps: 0.0");
    text->setPosition(0.01,0.95);
    addChild(text);

    FAGUIMaterialComponent *comp = new FAGUIMaterialComponent();
    // comp->setPosition(0.5,0.5);
    addChild(comp);

}

void testScene::render() {

}

void testScene::update(float dt) {
    
    text->setText(("fps: " + std::to_string(1/dt)));
}

void testScene::buttonPressed(int index) {
    
}

void testScene::getKeyInput(int key, int action) {
    
    if (key == GLFW_KEY_ESCAPE) {
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
        
}