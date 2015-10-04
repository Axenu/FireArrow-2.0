#ifndef __First__FADirectionalLight__
#define __First__FADirectionalLight__

#include "FALight.h"
#include "FACSMRenderPass.h"
#include "FAMaterialComponent.h"

class FADirectionalLight : public FALight {

private:
	float ambient;
	glm::vec3 direction;
	glm::vec4 color;
	GLuint *shadowMap;
	FACSMRenderPass *renderPass;

public:
	FADirectionalLight();

	virtual void onUpdate(float dt);

	void setColor(glm::vec4 &color);
	void setDirection(glm::vec3 direction);
	void setAmbientComponent(float ambientComponent);

	GLuint *getShadowMap();

	~FADirectionalLight();
	
};

#endif