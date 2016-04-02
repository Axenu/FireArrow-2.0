#ifndef __First__FAParticleSystem__
#define __First__FAParticleSystem__

#include <FA/FAMesh.h>
#include <algorithm>

struct FAParticle {
	glm::vec3 position;
	glm::vec3 speed;
	float life;
	float distance;
	
};



class FAParticleSystem : public FAMesh {
	
private:
	int maxParticleCount;
	GLuint quadBuffer;
	GLuint particleCenterBuffer;
	
	int numberOfParticles;
	int lastUnusedParticle;
	FAParticle *particles;
	float *centers;
	
	glm::vec3 *cameraPosition;
	
	void addParticle();
	int findParticleSpot();
	
public:
	
	FAParticleSystem();
	
	~FAParticleSystem();
	
	void render() const;
	void update(float dt);
	
	void setEyePosition(glm::vec3 *p);
	
};

#endif
