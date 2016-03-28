#include <FA/FAParticleSystem.h>


FAParticleSystem::FAParticleSystem() {
	
	maxParticleCount = 10000;
	numberOfParticles = 0;
	
	static const GLfloat quad[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};
	
	glGenBuffers(1, &quadBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	
	glGenBuffers(1, &particleCenterBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, particleCenterBuffer);
	glBufferData(GL_ARRAY_BUFFER, maxParticleCount * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, particleCenterBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	
}

FAParticleSystem::~FAParticleSystem() {
	
}

void FAParticleSystem::update(float dt) {
	
}

void FAParticleSystem::render() const {
	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, numberOfParticles);
}
