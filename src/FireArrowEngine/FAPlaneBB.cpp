#include <FA/FAPlaneBB.h>

FAPlaneBB::FAPlaneBB() {
	
}

FAPlaneBB::FAPlaneBB(glm::vec3 origin, glm::vec3 normal) {
	this->origin = origin;
	this->normal = normal;
	d = glm::dot(origin, normal);
}

FAPlaneBB::~FAPlaneBB() {
	
}

float FAPlaneBB::distance(const glm::vec3 &point) {
	return glm::dot(normal, point) - d;
}