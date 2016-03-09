#ifndef __First__FAAnimation__
#define __First__FAAnimation__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>

class FAAnimation {

private:

	std::vector<std::vector<glm::vec4>*> *keyframes;

public:
	FAAnimation();

	~FAAnimation();
	
};

#endif