#ifndef __First__FAShadowMapRenderPass__
#define __First__FAShadowMapRenderPass__

#include "FARenderPass.h"

class FAShadowMapRenderPass : public FARenderPass {

private:
	GLuint shadowMap;
    GLuint shadowFbo;
    FAShader *shader;
    GLint modelMatrixLocation;
    GLint viewProjectionMatrixLocation;
	glm::mat4 inverseShadowMatrix;

public:
	FAShadowMapRenderPass();
	~FAShadowMapRenderPass();

	void render();
	GLuint *getShadowMap();
	glm::mat4 *getInverseShadowMatrix();

};

#endif