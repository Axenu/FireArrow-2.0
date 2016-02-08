#ifndef FAShadowRenderPass_hpp
#define FAShadowRenderPass_hpp

#include <FA/FARenderPass.h>
#include <vector>

class FAShadowRenderPass : public FARenderPass {
	
private:
	
	
public:
	
	void setDirection(glm::vec3 *direction);
	void setModelMatrix(glm::mat4 *modelmatrix);
	std::vector<FAMaterialComponent *> getRequiredMaterialComponents();
	
	glm::vec3 *direction;
	glm::vec3 *position;
	
	glm::mat4 *modelmatrix;
	
protected:
	std::vector<FAMaterialComponent *> requiredMaterialComponents;
	
};

#endif
