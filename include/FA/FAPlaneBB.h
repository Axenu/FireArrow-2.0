#ifndef __First__FAPlaneBB__
#define __First__FAPlaneBB__

#include "FABoundingVolume.h"

class FAPlaneBB : public FABoundingVolume {
	
	
public:
	glm::vec3 origin;
	glm::vec3 normal;
	float d;
	
	FAPlaneBB();
	FAPlaneBB(glm::vec3 origin, glm::vec3 normal);
	
	~FAPlaneBB();
	
	float distance(const glm::vec3 &point);
};

#endif
