#ifndef __First__FAScene__
#define __First__FAScene__

#include <vector>
#include "FACamera.h"
#include "FAModel.h"
#include "FARenderPass.h"

class FARenderPass;

class FAScene {

private:
	FANode rootNode;
	int numberOfPasses;
	FARenderPass **renderPasses;
	std::vector<FAModel *> models;

	//testing
	FAModel *m;

public:
	FAScene();

	void render();
	void update(float dt);
	void addChild(FANode *child);
	void addRenderPass(FARenderPass *renderPass);

	std::vector<FAModel *> *getModels();
	// FACamera &getCamera();

	~FAScene();

protected:
	std::vector<FANode *> children;
	FACamera *camera;

};

#endif