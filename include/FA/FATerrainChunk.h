#ifndef __FireArrow__FATerrainChunk__
#define __FireArrow__FATerrainChunk__

#include <FA/FAMesh.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

class FATerrainChunk : public FAMesh {
	
private:
	
	int size;
	float tileSize;
	int heightMapSize;
	float **heightMap;
	glm::vec3 color;
	
	glm::vec3 **locations;
	GLfloat *vertices;
	int vertexCount;
	GLuint *indices;
	
	void addTile(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3, glm::vec3 &v4);
	const glm::vec3 calculateNormal(glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &p3);
	
public:
	FATerrainChunk();
	
	void loadChunk();
	
	float getHeight(float x, float z);
	
	~FATerrainChunk();
	
};

#endif