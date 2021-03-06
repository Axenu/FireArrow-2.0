#ifndef __First__FACSMRenderPass__
#define __First__FACSMRenderPass__

#include "FAShadowRenderPass.h"

class FACSMRenderPass : public FAShadowRenderPass {

private:
	GLuint shadowMap;
    GLuint shadowFbo;
    FAShader *shader;
    GLint modelMatrixLocation;
    GLint viewProjectionMatrixLocation;
//    glm::vec3 *direction;

	int frustums = 4; //remove static definition
	glm::mat4 *inverseShadowMatrix;

	glm::mat4 calculateShadowCamera(float near, float far);

public:
	FACSMRenderPass();
	~FACSMRenderPass();

	void render();
	GLuint *getShadowMap();
	glm::mat4 *getInverseShadowMatrix();
	int *getFrustums();
	//	void setDirection(glm::vec3 *direction);
//	std::vector<FAMaterialComponent *> getRequiredMaterialComponents();

};

#endif