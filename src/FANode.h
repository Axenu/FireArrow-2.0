#ifndef __First__FANode__
#define __First__FANode__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>

class FANode {
	float x, y, z;
	std::vector<FANode *> children;

public:
	FANode();

	void setPosition(float x, float y, float z);
	void addChild(FANode *child);
	std::vector<FANode *> getAllChildren();

	virtual ~FANode();

protected:
	glm::vec3 position;
	glm::vec3 rotation;
};


#endif