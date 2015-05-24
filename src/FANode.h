#ifndef __First__FANode__
#define __First__FANode__

#include <vector>

class FANode {
	float x, y, z;
	std::vector<FANode *> children;

public:
	FANode();

	void setPosition(float x, float y, float z);
	void addChild(FANode *child);
	std::vector<FANode *> getAllChildren();
};


#endif