#ifndef __First__testScene__
#define __First__testScene__

#include <dirent.h>
#include <FA/FAScene.h>
#include <FA/FAGUILabel.h>
#include <FA/FATerrain.h>
#include <FA/FATexture.h>
#include <FA/FADirectionalLight.h>
#include <FA/FAAmbientLight.h>
#include <FA/FAPointLight.h>
#include <FA/FAShadowMapRenderPass.h>
#include <FA/FAGUITexturedPlane.h>
#include <FA/FAGUIMaterialComponent.h>
#include <FA/FAGUIButton.h>
#include <FA/FAGUIMenu.h>
#include "Material.h"
#include "SkinningMaterial.h"
#include "NormalMaterial.h"
#include <FA/FAGaussianRenderPass.h>

class testScene : public FAScene {
    
private:
    const float speed = 5;
    bool cursorHasMoved = false;
    glm::vec2 previousCursorPosition;
    glm::vec3 cameraMovement;
    FAFont *font;
    FAGUILabel *text;
    float time;
    float frames;
	FAMesh *animated;
	glm::vec3 direction;
	FATerrainChunk *ch;
	
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