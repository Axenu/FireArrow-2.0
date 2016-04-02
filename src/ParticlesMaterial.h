#ifndef __First__ParticlesMaterial__
#define __First__ParticlesMaterial__

#define GLM_FORCE_RADIANS

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <FA/FAMaterial.h>

class ParticlesMaterial : public FAMaterial {
	
private:
	FAShader *shader;
	glm::mat4 viewProjectionMatrix;
	
	GLint VPLocation;
	GLint cameraPositionLocation;
	
public:
	ParticlesMaterial();
	~ParticlesMaterial();
	
	void bind();
	void setViewProjectionwMatrix(glm::mat4 &VPMatrix);
};

#endif
