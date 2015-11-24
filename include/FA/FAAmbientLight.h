#ifndef __First__FAAmbientLight__
#define __First__FAAmbientLight__

#include "FALight.h"
#include "FAMaterialComponent.h"

class FAAmbientLight : public FALight {

private:
	float strength;
	glm::vec4 color;
	glm::vec4 finalColor;

public:
	FAAmbientLight();
	FAAmbientLight(glm::vec4 &color, float strength);

	virtual void onUpdate(float dt);

	void setColor(glm::vec4 &color);
	void setAmbientComponent(float ambientComponent);


	~FAAmbientLight();
	
};

#endif