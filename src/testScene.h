#ifndef __First__testScene__
#define __First__testScene__

#include <dirent.h>
#include <FA/FAScene.h>
#include <FA/FAText.h>
#include <FA/FATerrain.h>
#include <FA/FATexture.h>

class testScene : public FAScene {
    
private:
    // FATexturedPlane2D *albumArt;
    // FAPipeline *p;
    // FAModel *player;
    // Leap::Controller *controller;
    
    const float speed = 5;
    bool cursorHasMoved = false;
    glm::vec2 previousCursorPosition;
    glm::vec3 cameraMovement;
    FAText *text;
    FAFont *font;
    
public:
    void init();
    void render();
    void update(float dt);
        using FAScene::getKeyInput;
    void buttonPressed(int index);
    void getKeyInput(int key, int action);
    void mouseKeyInput(int button, int action);
    void cursorPosition(double x, double y);
    
};

#endif