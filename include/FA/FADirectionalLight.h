#ifndef __First__FADirectionalLight__
#define __First__FADirectionalLight__

#include "FALight.h"
#include "FACSMRenderPass.h"
#include "FAMaterialComponent.h"

class FADirectionalLight : public FALight {

private:
//	glm::vec3 direction;
	GLuint *shadowMap;
	FADirectionalLightComponent *lightComponent;
	FAShadowRenderPass *renderPass;
	//change to any shadow pass

public:
	FADirectionalLight();

	virtual void onUpdate(float dt);

	void setDirection(glm::vec3 direction);
	void setShadowMap(FAShadowRenderPass &pass);

	GLuint *getShadowMap();

	~FADirectionalLight();
	
};

#endif