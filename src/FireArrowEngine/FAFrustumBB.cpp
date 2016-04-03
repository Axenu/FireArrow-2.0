#include <FA/FAFrustumBB.h>

FAFrustumBB::FAFrustumBB() {
	
}

FAFrustumBB::FAFrustumBB(float fov, float ratio, float near, float far) {
	this->fieldOfView = fov;
	this->aspectRation = ratio;
	this->nearPlane = near;
	this->farPlane = far;
	
	float tanAngle = tanf(this->fieldOfView * (glm::pi<float>() / 360.0f));
	this->nearHeight = nearPlane * tanAngle;
	this->nearWidth = this->nearHeight * this->aspectRation;
	this->farHeight = farPlane * tanAngle;
	this->farWidth = this->farHeight * this->aspectRation;
}

FAFrustumBB::~FAFrustumBB() {
	
}

void FAFrustumBB::calculateFrustumPlanes(const glm::mat4 &viewMatrix, const glm::vec3 &cameraPosition) {
	look = glm::normalize(glm::vec3(-viewMatrix[0][2],-viewMatrix[1][2],-viewMatrix[2][2]));
	up = glm::normalize(glm::vec3(viewMatrix[0][1],viewMatrix[1][1],viewMatrix[2][1]));
	right = glm::cross(up, look);
	
	nearCenter = look * this->nearPlane;
	farCenter = look * this->farPlane;
	
	planes[5] = FAPlaneBB(nearCenter + cameraPosition, look);
	planes[4] = FAPlaneBB(farCenter + cameraPosition, -look);
	
	glm::vec3 line, normal;
	line = glm::normalize((nearCenter + up*nearHeight));
	normal = glm::cross(line, right);
	planes[0] = FAPlaneBB(nearCenter+up*nearHeight + cameraPosition, normal);
	
	line = glm::normalize((nearCenter -up*nearHeight));
	normal = glm::cross(right, line);
	planes[1] = FAPlaneBB(nearCenter - up * nearHeight + cameraPosition, normal);
	
	line = glm::normalize((nearCenter + right * nearWidth));
	normal = glm::cross(line, up);
	planes[2] = FAPlaneBB(nearCenter + right * nearWidth + cameraPosition, normal);
	
	line = glm::normalize((nearCenter - right * nearWidth));
	normal = glm::cross(up, line);
	planes[3] = FAPlaneBB(nearCenter - right * nearWidth + cameraPosition, normal);
	
	nearCenter += cameraPosition;
	farCenter += cameraPosition;

}

bool FAFrustumBB::collideWith(const FASphereBB &other) {
	
	float distance;
	bool intersects = false;
	
	for (int i = 0; i < 6; i++) {
		distance = planes[i].distance(other.center);
		if (distance < -other.radius) {
			return false;
		} else if (distance < other.radius) {
			intersects = true;
		}
	}
	
	return intersects;
}

bool FAFrustumBB::collideWith(const FAAABB &other) {
	
//	bool intersects = false;
	
	for (int i = 2; i < 6; i++) {
//		glm::vec3 pp = other.getPositive(planes[i].normal);
		float d = planes[i].distance(other.getPositive(planes[i].normal));
		if (d < 0) {
			return false;
		}
		
	}
	
	return true;
}

void FAFrustumBB::calculateMesh() {
	glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
	
	ntr = nearCenter + up * nearHeight + right * nearWidth;
	ntl = nearCenter + up * nearHeight - right * nearWidth;
	nbr = nearCenter - up * nearHeight + right * nearWidth;
	nbl = nearCenter - up * nearHeight - right * nearWidth;
	
	ftr = farCenter + up * farHeight + right * farWidth;
	ftl = farCenter + up * farHeight - right * farWidth;
	fbr = farCenter - up * farHeight + right * farWidth;
	fbl = farCenter - up * farHeight - right * farWidth;
	
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
	
	vertices.push_back(ntr.x);
	vertices.push_back(ntr.y);
	vertices.push_back(ntr.z);
	
	vertices.push_back(ftr.x);
	vertices.push_back(ftr.y);
	vertices.push_back(ftr.z);
	
	vertices.push_back(nbr.x);
	vertices.push_back(nbr.y);
	vertices.push_back(nbr.z);
	
	vertices.push_back(fbr.x);
	vertices.push_back(fbr.y);
	vertices.push_back(fbr.z);
	
	vertices.push_back(ntl.x);
	vertices.push_back(ntl.y);
	vertices.push_back(ntl.z);
	
	vertices.push_back(ftl.x);
	vertices.push_back(ftl.y);
	vertices.push_back(ftl.z);
	
	vertices.push_back(nbl.x);
	vertices.push_back(nbl.y);
	vertices.push_back(nbl.z);
	
	vertices.push_back(fbl.x);
	vertices.push_back(fbl.y);
	vertices.push_back(fbl.z);
	
}

std::vector<GLfloat> &FAFrustumBB::getVertices() {
	return this->vertices;
}

std::vector<GLuint> &FAFrustumBB::getIndices() {
	return this->indices;
}











