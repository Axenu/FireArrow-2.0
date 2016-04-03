#ifndef __First__FAAABB__
#define __First__FAAABB__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include "FABoundingVolume.h"
#include <vector>


class FAAABB : public FABoundingVolume {
private:
	
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	
public:
	glm::vec3 half;
	glm::vec3 globalCenter;
	
	FAAABB();
	FAAABB(glm::vec3 center, glm::vec3 half);
	
	bool contains(const FAAABB &other);
	glm::vec3 getPositive(const glm::vec3 &normal) const;
	
	void calculateMesh();
	std::vector<GLfloat> &getVertices();
	std::vector<GLuint> &getIndices();
	
	~FAAABB();
	
};

#endif