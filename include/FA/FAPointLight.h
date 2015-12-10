#ifndef __First__FAPointLight__
#define __First__FAPointLight__

#include "FALight.h"
#include "FAMaterialComponent.h"

class FAPointLight : public FALight {

private:
	float radius = 15.0f;

public:
	FAPointLight();

	virtual void onUpdate(float dt);
	
	void setRadius(float radius);

	~FAPointLight();
	
};

#endif