#include <FA/FAParticleSystem.h>


FAParticleSystem::FAParticleSystem() {
	
	maxParticleCount = 10000;
	numberOfParticles = 0;
	particles = new FAParticle[maxParticleCount];
	centers = new float[maxParticleCount * 3];
	lastUnusedParticle = 0;
	
	static const GLfloat quad[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};
	
	glGenBuffers(1, &quadBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, &quad[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &particleCenterBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, particleCenterBuffer);
	glBufferData(GL_ARRAY_BUFFER, maxParticleCount * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, particleCenterBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(1, 1);
	
	
	srand ((uint)time(NULL));
	
}

FAParticleSystem::~FAParticleSystem() {
	delete particles;
	delete centers;
	delete cameraPosition;
	
	glDeleteBuffers(1, &quadBuffer);
	glDeleteBuffers(1, &particleCenterBuffer);
	glDeleteVertexArrays(1, &VAO);
}

bool compare(FAParticle const&lhs, FAParticle const&rhs) {
	return lhs.distance > rhs.distance;
}

void FAParticleSystem::update(float dt) {
	
	addParticle();
	
	//update particles
	numberOfParticles = 0;
	
	for (int i = 0; i < maxParticleCount; i++) {
		FAParticle &p = particles[i];
		if (p.life > 0.0) {
			p.life -= dt;
			if (p.life > 0.0) {
				
				p.position += p.speed * dt;
				p.distance = glm::length2(p.position - *cameraPosition);
				
				centers[3*i] = p.position.x;
				centers[3*i+1] = p.position.y;
				centers[3*i+2] = p.position.z;
				
				numberOfParticles++;
			} else {
				p.distance = -1;
			}
		}
	}
	
	std::sort(particles, particles + maxParticleCount, &compare);
	
	for (int i = 0; i < maxParticleCount; i++) {
		centers[i*3] = particles[i].position.x;
		centers[i*3+1] = particles[i].position.y;
		centers[i*3+2] = particles[i].position.z;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, particleCenterBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, numberOfParticles * 3 * sizeof(GLfloat), &centers[0]);
	
}

void FAParticleSystem::render() const {
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numberOfParticles);
}

void FAParticleSystem::addParticle() {
	//add new particles
	FAParticle &pa = particles[findParticleSpot()];
	pa.position = glm::vec3((rand() %100 - 50)/500.0,(rand() %100 - 50)/500.0,(rand() %100 - 50)/500.0);
	pa.life = 2;
	pa.speed = glm::vec3((rand() %100 - 50)/100.0,0.5,(rand() %100 - 50)/100.0);
}

int FAParticleSystem::findParticleSpot() {
	
	for (int i = lastUnusedParticle; i < maxParticleCount; i++) {
		if (particles[i].life <= 0.0) {
			lastUnusedParticle = i;
			return i;
		}
	}
	
	for (int i = 0; i < lastUnusedParticle; i++) {
		if (particles[i].life <= 0.0) {
			lastUnusedParticle = i;
			return i;
		}
	}
	return lastUnusedParticle++;
}

void FAParticleSystem::setEyePosition(glm::vec3 *p) {
	this->cameraPosition = p;
}
