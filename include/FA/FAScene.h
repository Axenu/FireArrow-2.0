#ifndef __First__FAScene__
#define __First__FAScene__

#include <vector>
#include "FACamera.h"
#include "FAModel.h"
#include "FARenderPass.h"
#include "FAMainRenderPass.h"
#include "FACSMRenderPass.h"

// class FARenderPass;
class FAEngine;

class FAScene : FARenderPasscallbackInterface {

private:

public:

	FAScene();

	void onInit();
    void onUpdate(float dt);
    void onRender();

	void addChild(FANode *child);
	void addRenderPass(FARenderPass *renderPass);

	void setCallback(FAEngine* _callback);
	void setWindowSize(int width, int height);
	void setCursorState(int state);

	void getMouseKeyInput(int button, int action);
	void getCursorPosition(double x, double y);
	int getCursorState();

	std::vector<FAModel *> *getModels();
	FACamera *getCamera();
	float getWindowWidths();

	~FAScene();

	virtual void init(){}
    virtual void render(){}
    virtual void update(float dt){}
    virtual void getKeyInput(int key, int action){}
    virtual void mouseKeyInput(int button, int action){}
    virtual void cursorPosition(double x, double y){}
    // virtual void buttonPressed(FAHUDElement *node){}

protected:
	FANode rootNode;
	int numberOfPasses;
	FARenderPass **renderPasses;
	std::vector<FAModel *> models;
	bool isActive;
	FAEngine* callback;
    int windowWidth;
    int windowHeigth;
	std::vector<FANode *> children;
	FACamera *camera;

};

#endif