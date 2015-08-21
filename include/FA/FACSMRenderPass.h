#ifndef __First__FACSMRenderPass__
#define __First__FACSMRenderPass__

#include "FARenderPass.h"

class FACSMRenderPass : public FARenderPass {

private:
	GLuint shadowMap;
    GLuint shadowFbo;
    FAShader shader;
    GLint modelMatrixLocation;
    GLint viewProjectionMatrixLocation;

	int frustums = 4; //remove static definition
	glm::mat4 *inverseShadowMatrix;

	glm::mat4 calculateShadowCamera(float near, float far);

public:
	FACSMRenderPass();
	~FACSMRenderPass();

	void render();

};

#endif