#ifndef __First__FAFrustumBB__
#define __First__FAFrustumBB__

#include "FABoundingVolume.h"
#include "FAPlaneBB.h"
#include "FASphereBB.h"
#include "FAAABB.h"

class FAFrustumBB : public FABoundingVolume {
private:
	FAPlaneBB planes[6]; //0:top, 1:bottom, 2:right, 3:left, 4:far, 5:near
	float fieldOfView;
	float aspectRation;
	float farPlane;
	float nearPlane;
	float nearWidth, nearHeight, farWidth, farHeight;
	glm::vec3 look, up, right;
	glm::vec3 nearCenter, farCenter;
	
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	
public:
	
	FAFrustumBB();
	FAFrustumBB(float fov, float ratio, float near, float far);
	~FAFrustumBB();
	
	void calculateFrustumPlanes(const glm::mat4 &viewMatrix, const glm::vec3 &cameraPosition);
	
	bool collideWith(const FASphereBB &other);
	bool collideWith(const FAAABB &other);
	
	void calculateMesh();
	std::vector<GLfloat> &getVertices();
	std::vector<GLuint> &getIndices();
	
};

#endif
