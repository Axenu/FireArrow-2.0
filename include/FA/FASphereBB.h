#ifndef __First__FASphereBB__
#define __First__FASphereBB__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class FASphereBB {
	
	
public:
	glm::vec3 center;
	float radius;
	
	FASphereBB();
	~FASphereBB();
};

#endif /* FASphereBB_h */
