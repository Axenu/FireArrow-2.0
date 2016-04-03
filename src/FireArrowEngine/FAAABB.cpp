#include <FA/FAAABB.h>

FAAABB::FAAABB() {
	this->center = glm::vec3(0,0,0);
	this->half = glm::vec3(0,0,0);
}

FAAABB::FAAABB(glm::vec3 center, glm::vec3 half) {
	this->center = center;
	this->globalCenter = center;
	this->half = half;
}
//
//FAAABB::FAAABB(glm::vec3 &min, glm::vec3 &max) {
//}

bool FAAABB::contains(const FAAABB &other) {
	
	if (other.globalCenter.x + other.half.x < this->globalCenter.x + this->half.x && other.globalCenter.x - other.half.x >= this->globalCenter.x - this->half.x) {
		if (other.globalCenter.y + other.half.y < this->globalCenter.y + this->half.y && other.globalCenter.y - other.half.y >= this->globalCenter.y - this->half.y) {
			if (other.globalCenter.z + other.half.z < this->globalCenter.z + this->half.z && other.globalCenter.z - other.half.z >= this->globalCenter.z - this->half.z) {
				return true;
			}
		}
	}
	return false;
}

glm::vec3 FAAABB::getPositive(const glm::vec3 &normal) const {
	glm::vec3 p = glm::vec3(center);
	
	if (normal.x >= 0.0) {
		p.x += half.x;
	} else {p.x -= half.x;}
	if (normal.y >= 0.0) {
		p.y += half.y;
	} else {p.y -= half.y;}
	if (normal.z >= 0.0) {
		p.z += half.z;
	} else {p.z -= half.z;}
	
	return p;
}


void FAAABB::calculateMesh() {
	if (indices.size() < 24) {
		indices.push_back(0);
		indices.push_back(4);
		
		indices.push_back(0);
		indices.push_back(1);
		
		indices.push_back(0);
		indices.push_back(2);
		
		indices.push_back(1);
		indices.push_back(3);
		
		indices.push_back(1);
		indices.push_back(5);
		
		indices.push_back(2);
		indices.push_back(3);
		
		indices.push_back(2);
		indices.push_back(6);
		
		indices.push_back(4);
		indices.push_back(6);
		
		indices.push_back(4);
		indices.push_back(5);
		
		indices.push_back(7);
		indices.push_back(3);
		
		indices.push_back(7);
		indices.push_back(5);
		
		indices.push_back(7);
		indices.push_back(6);
	}
	
	vertices.push_back(center.x + half.x);
	vertices.push_back(center.y + half.y);
	vertices.push_back(center.z + half.z);
	
	vertices.push_back(center.x + half.x);
	vertices.push_back(center.y + half.y);
	vertices.push_back(center.z - half.z);
	
	vertices.push_back(center.x + half.x);
	vertices.push_back(center.y - half.y);
	vertices.push_back(center.z + half.z);
	
	vertices.push_back(center.x + half.x);
	vertices.push_back(center.y - half.y);
	vertices.push_back(center.z - half.z);
	
	vertices.push_back(center.x - half.x);
	vertices.push_back(center.y + half.y);
	vertices.push_back(center.z + half.z);
	
	vertices.push_back(center.x - half.x);
	vertices.push_back(center.y + half.y);
	vertices.push_back(center.z - half.z);
	
	vertices.push_back(center.x - half.x);
	vertices.push_back(center.y - half.y);
	vertices.push_back(center.z + half.z);
	
	vertices.push_back(center.x - half.x);
	vertices.push_back(center.y - half.y);
	vertices.push_back(center.z - half.z);
}

std::vector<GLfloat> &FAAABB::getVertices() {
	return this->vertices;
}

std::vector<GLuint> &FAAABB::getIndices() {
	return this->indices;
}


FAAABB::~FAAABB() {
	
}