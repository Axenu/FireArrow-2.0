#ifndef __First__FALight__
#define __First__FALight__

#include "FANode.h"
#include "FARenderPass.h"

class FALight : public FANode {

private:
	bool _hasShadow;
public:
	FALight();

	virtual void onUpdate(float dt);
	void setColor(glm::vec4 &color);

	bool hasShadow();

	std::vector<FARenderPass *> *getRequirements();
	std::vector<FAMaterialComponent *> *getMaterialRequirements();

	~FALight();

protected:
	std::vector<FARenderPass *> requirements;
	std::vector<FAMaterialComponent *> materialRequirements;
	glm::vec4 color;
	
};

#endif