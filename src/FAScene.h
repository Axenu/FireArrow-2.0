#ifndef __First__FAScene__
#define __First__FAScene__

#include <vector>
#include "FANode.h"

class FAScene {

private:
	FANode rootNode;
	std::vector<FANode *> children;

public:
	FAScene();
	~FAScene();

	void render();
	void update(float dt);
	void addChild(FANode *child);
	
};

#endif