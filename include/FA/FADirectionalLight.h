#ifndef __First__FADirectionalLight__
#define __First__FADirectionalLight__

#include "FALight.h"
#include "FACSMRenderPass.h"
#include "FAMaterialComponent.h"

class FADirectionalLight : public FALight {

private:
	glm::vec3 direction;
	GLuint *shadowMap;
	FACSMRenderPass *renderPass;

public:
	FADirectionalLight();

	virtual void onUpdate(float dt);

	void setDirection(glm::vec3 direction);

	GLuint *getShadowMap();

	~FADirectionalLight();
	
};

#endif