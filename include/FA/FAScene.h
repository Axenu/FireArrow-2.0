#ifndef __First__FAScene__
#define __First__FAScene__

#include <vector>
#include "FACamera.h"
#include "FAModel.h"
#include "FAMainRenderPass.h"
#include "FACSMRenderPass.h"
#include "FALight.h"
#include "FAGUILabel.h"
#include "FAQuadTree.h"

// class FARenderPass;
class FAEngine;

class FAScene : FARenderPasscallbackInterface {

private:
	glm::vec2 lastCursorPosition;
	FAGUIElement *currentElement = nullptr;
	FAMainRenderPass *defaultPass;

public:

	FAScene();

	void onInit();
    void onUpdate(float dt);
    void onRender();

    void addChild(FAGUIElement *child);
	void addChild(FANode *child);
	void addRenderPass(FARenderPass *renderPass);

	void setCallback(FAEngine* _callback);
	void setWindowSize(int width, int height);
	void setCursorState(int state);

	void getMouseKeyInput(int button, int action);
	void getCursorPosition(double x, double y);
	int getCursorState();

	void cullModels(FACamera *cam);
	
	std::vector<FAModel *> *getModels();
	FACamera *getCamera();
	FACamera *getCullCamera();
	float getWindowWidths();

	~FAScene();

	virtual void init(){}
    virtual void render(){}
    virtual void update(float dt){}
    virtual void getKeyInput(int key, int action){}
    virtual void mouseKeyInput(int button, int action){}
    virtual void cursorPosition(double x, double y){}
	FAMainRenderPass *getMainPass() {return defaultPass;}
    // virtual void buttonPressed(FAHUDElement *node){}

protected:
	FANode rootNode;
	int numberOfPasses;
	FARenderPass **renderPasses;
	std::vector<FAModel *> models;
	std::vector<FAModel *> culledModels;
	std::vector<FALight *> lights;
	std::vector<FAGUIElement *> GUIElements;
	std::vector<FAMaterialComponent *> requiredComponents;
	bool isActive;
	FAEngine* callback;
    int windowWidth;
    int windowHeigth;
	std::vector<FANode *> children;
	FAQuadTree *childTree;
	FACamera *camera;
	FACamera *cullCamera;

};

#endif