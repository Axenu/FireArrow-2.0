#ifndef __First__testScene__
#define __First__testScene__

#include <dirent.h>
#include <FA/FAScene.h>
#include <FA/FAGUIText.h>
#include <FA/FATerrain.h>
#include <FA/FATexture.h>
#include <FA/FADirectionalLight.h>
#include <FA/FAShadowMapRenderPass.h>
#include <FA/FAGUITexturedPlane.h>
#include <FA/FAGUIMaterialComponent.h>

class testScene : public FAScene {
    
private:
    FAFont *font;
    FAGUIText *text;
    
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