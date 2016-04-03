#include <FA/FATerrainChunk.h>

FATerrainChunk::FATerrainChunk() {
	this->size = 100;
	this->tileSize = 1;
	this->heightMap = nullptr;
	this->heightMapSize = 10;
	this->color = glm::vec3(0.1,0.5,0.1);
}


void FATerrainChunk::loadChunk() {
	
	//use file
	
	heightMap = new float*[heightMapSize];
	for (int i = 0; i < heightMapSize; ++i) {
		heightMap[i] = new float[heightMapSize];
		for (int x = 0; x < heightMapSize; x++) {
			heightMap[i][x] = 0;
		}
	}
//	
	heightMap[1][1] = 10;
//	heightMap[1][2] = 10;

	
	locations = new glm::vec3*[size + 1];
	for (int i = 0; i < size + 1; ++i) {
		locations[i] = new glm::vec3[size + 1];
	}
	
//	std::vector<GLfloat> vertices;
	std::vector<glm::vec3> verticesTemp;
//	std::vector<GLuint> indices;
	
	srand ((uint)time(NULL));
	
	float xx = 0;
	float zz = 0;
	
	for (GLfloat x = -size/2.0; x <= size/2.0; x += tileSize) {
		for (GLfloat z = -size/2.0; z <= size/2.0; z += tileSize) {
			float height = 0;
			float xvalue = xx*((float)(heightMapSize-1)/(size+1));
			float yvalue = zz*((float)(heightMapSize-1)/(size+1));
			int lowx = glm::floor(xvalue);
			int highx = lowx + 1;
			int lowy = glm::floor(yvalue);
			int highy = lowy + 1;
			
			float highm = heightMap[lowx][highy] - heightMap[highx][highy];
			float lowm = heightMap[lowx][lowy] - heightMap[highx][lowy];
			
			float high = heightMap[lowx][highy] - highm * (xvalue - lowx);
			
			float low = heightMap[lowx][lowy] - lowm * (xvalue - lowx);
			
			float lastm = low - high;
			
			height = low - lastm * (yvalue - lowy);
			
			locations[(int)xx][(int)zz] = glm::vec3(x,height,z);
			zz++;
		}
		xx++;
		zz = 0;
	}
	
	vertices = new GLfloat[size*size*54];
	indices = new GLuint[size*size*6];
	vertexCount = 0;
	
	//loop through and assign vertices and indices
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			addTile(locations[x][y], locations[x+1][y], locations[x+1][y+1], locations[x][y+1]);
		}
		
	}
	//TODO remove indices from flatshading models
	for (int i = 0; i < size*size*6; i++) {
		indices[i] = i;
	}
	
//	avaliableVertexComponents.push_back(new FAVertexColorComponent());
//	avaliableVertexComponents.push_back(new FAVertexNormalComponent());
	// this->_hasPosition = true;
	
	// load model to graphicscard
	this->numberOfVertices = (GLint) size*size*6;
	
	//test
	// GLfloat vertA[] = {0,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,1,0, 1,0,0, 1,0,0, 0,1,0, 1,0,0, 1,0,0};
	// GLuint indA[] = {0,1,2,0,2,3};
	// _hasColor = true;
	// _hasNormal = true;
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size*size*54 * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfVertices * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *) (6 * sizeof(GLfloat)));
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void FATerrainChunk::addTile(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3, glm::vec3 &v4) {
	glm::vec3 normal = calculateNormal(v1, v4, v2);
	vertices[vertexCount++] = v1.x;
	vertices[vertexCount++] = v1.y;
	vertices[vertexCount++] = v1.z;
	vertices[vertexCount++] = normal.x;
	vertices[vertexCount++] = normal.y;
	vertices[vertexCount++] = normal.z;
	vertices[vertexCount++] = color.x;
	vertices[vertexCount++] = color.y;
	vertices[vertexCount++] = color.z;
	vertices[vertexCount++] = v4.x;
	vertices[vertexCount++] = v4.y;
	vertices[vertexCount++] = v4.z;
	vertices[vertexCount++] = normal.x;
	vertices[vertexCount++] = normal.y;
	vertices[vertexCount++] = normal.z;
	vertices[vertexCount++] = color.x;
	vertices[vertexCount++] = color.y;
	vertices[vertexCount++] = color.z;
	vertices[vertexCount++] = v2.x;
	vertices[vertexCount++] = v2.y;
	vertices[vertexCount++] = v2.z;
	vertices[vertexCount++] = normal.x;
	vertices[vertexCount++] = normal.y;
	vertices[vertexCount++] = normal.z;
	vertices[vertexCount++] = color.x;
	vertices[vertexCount++] = color.y;
	vertices[vertexCount++] = color.z;
	normal = calculateNormal(v2, v4, v3);
	vertices[vertexCount++] = v2.x;
	vertices[vertexCount++] = v2.y;
	vertices[vertexCount++] = v2.z;
	vertices[vertexCount++] = normal.x;
	vertices[vertexCount++] = normal.y;
	vertices[vertexCount++] = normal.z;
	vertices[vertexCount++] = color.x;
	vertices[vertexCount++] = color.y;
	vertices[vertexCount++] = color.z;
	vertices[vertexCount++] = v4.x;
	vertices[vertexCount++] = v4.y;
	vertices[vertexCount++] = v4.z;
	vertices[vertexCount++] = normal.x;
	vertices[vertexCount++] = normal.y;
	vertices[vertexCount++] = normal.z;
	vertices[vertexCount++] = color.x;
	vertices[vertexCount++] = color.y;
	vertices[vertexCount++] = color.z;
	vertices[vertexCount++] = v3.x;
	vertices[vertexCount++] = v3.y;
	vertices[vertexCount++] = v3.z;
	vertices[vertexCount++] = normal.x;
	vertices[vertexCount++] = normal.y;
	vertices[vertexCount++] = normal.z;
	vertices[vertexCount++] = color.x;
	vertices[vertexCount++] = color.y;
	vertices[vertexCount++] = color.z;
}

const glm::vec3 FATerrainChunk::calculateNormal(glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &p3) {
	glm::vec3 v1 = p2 - p1;
	glm::vec3 v2 = p3 - p1;
	
	return glm::normalize(glm::cross(v1, v2));
}

float FATerrainChunk::getHeight(float x, float z) {
	
	if (x < -size/2.0 || z < -size/2.0 || x > size/2.0 || z > size/2.0) {
		return 0;
	}
	
	float diffx = x + size/2.0;
	float diffz = z + size/2.0;
	
	int lowx = floor(diffx/tileSize);
	int highx = lowx + 1;
	int lowz = floor(diffz/tileSize);
	int highz = lowz + 1;
	
	float highm = locations[lowx][highz].y - locations[highx][highz].y;
	float lowm = locations[lowx][lowz].y - locations[highx][lowz].y;
	
	float high = locations[lowx][highz].y - highm * (diffx - lowx);
	
	float low = locations[lowx][lowz].y - lowm * (diffx - lowx);
	
	float lastm = low - high;
	
//	height = low - lastm * (z - lowz);
	
//	return interpolateheight(locations[lowx][lowz].y, locations[highx][lowz].y, locations[highx][highz].y, locations[lowx][highz].y, x, z);
//	std::cout << low - lastm * (diffz - lowz) << std::endl;
	return low - lastm * (diffz - lowz);
}


FATerrainChunk::~FATerrainChunk() {
	for (int i = 0; i < heightMapSize; i++) {
		delete[]heightMap[i];
	}
	delete[]heightMap;
	for (int i = 0; i < size + 1; ++i) {
		delete [] locations;
	}
	delete [] locations;
	delete [] indices;
	delete [] vertices;
}