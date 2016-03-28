#ifndef __First__FAParticleSystem__
#define __First__FAParticleSystem__

#include <FA/FAMesh.h>

struct FAParticle {
	glm::vec3 position;
	glm::vec3 speed;
	float life;
};

class FAParticleSystem : public FAMesh {
	
private:
	int maxParticleCount;
	GLuint quadBuffer;
	GLuint particleCenterBuffer;
	
	int numberOfParticles;
	
public:
	
	FAParticleSystem();
	
	~FAParticleSystem();
	
	void render() const;
	void update(float dt);
	
};

#endif
