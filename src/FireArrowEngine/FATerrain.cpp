#include <FA/FATerrain.h>

void generateHeightMap() {

}

FATerrain::FATerrain() {

	//defualt
	int size = 100;
	int tileSize = 1;
	float heightMapSize = 50;

	//heightmap
	float **map = new float*[50];
	for (int i = 0; i < 50; ++i) {
		map[i] = new float[50];
		for (int x = 0; x < 50; x++) {
			map[i][x] = 0;
		}
	}

	// map[25][24] = 1;
	map[25][23] = 2;
	map[25][22] = -3;
	map[25][21] = 4;

	map[22][21] = 10;

	std::vector<GLfloat> vertices;
	std::vector<glm::vec3> verticesTemp;
	std::vector<GLuint> indices;

	srand (time(NULL));

	float xx = 0;
	float yy = 0;

	for (GLfloat x = -size/2.0; x <= size/2.0; x += tileSize) {
		for (GLfloat y = -size/2.0; y <= size/2.0; y += tileSize) {
			float height = 0;
			float xvalue = xx*((heightMapSize-1)/(size+1));
			float yvalue = yy*((heightMapSize-1)/(size+1));
			int lowx = glm::floor(xvalue);
			int highx = lowx + 1;
			int lowy = glm::floor(yvalue);
			int highy = lowy + 1;

			float highm = map[lowx][highy] - map[highx][highy];
			float lowm = map[lowx][lowy] - map[highx][lowy];

			float high = map[lowx][highy] - highm * (xvalue - lowx);

			float low = map[lowx][lowy] - lowm * (xvalue - lowx);

			float lastm = low - high;

			height = low - lastm * (yvalue - lowy);

			verticesTemp.push_back(glm::vec3(x,height,y));
			yy++;
		}
		xx++;
		yy = 0;
	}
	for (int x = 0; x < size; x++) {
		for (int i = 0; i < size; i++) {
			glm::vec3 color = glm::vec3(0.1,0.5,0.1);

			glm::vec3 p1 = verticesTemp[(size+1)*x+i];
			glm::vec3 p2 = verticesTemp[(size+1)*x+1+i];
			glm::vec3 p3 = verticesTemp[(size+1)*(x+1)+i];
			
			glm::vec3 v1 = p2 - p1;
			glm::vec3 v2 = p3 - p1;
			
			glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

			vertices.push_back(p1[0]);
			vertices.push_back(p1[1]);
			vertices.push_back(p1[2]);
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
			vertices.push_back(color.x);
			vertices.push_back(color.y);
			vertices.push_back(color.z);
			vertices.push_back(p2[0]);
			vertices.push_back(p2[1]);
			vertices.push_back(p2[2]);
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
			vertices.push_back(color.x);
			vertices.push_back(color.y);
			vertices.push_back(color.z);
			vertices.push_back(p3[0]);
			vertices.push_back(p3[1]);
			vertices.push_back(p3[2]);
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
			vertices.push_back(color.x);
			vertices.push_back(color.y);
			vertices.push_back(color.z);

			p1 = verticesTemp[(size+1)*x+1+i];
			p2 = verticesTemp[(size+1)*(x+1)+i+1];
			p3 = verticesTemp[(size+1)*(x+1)+i];
			
			v1 = p2 - p1;
			v2 = p3 - p1;
			
			normal = glm::normalize(glm::cross(v1, v2));
			// color = glm::vec3(rand()%2,rand()%2,rand()%2);


			vertices.push_back(p1[0]);
			vertices.push_back(p1[1]);
			vertices.push_back(p1[2]);
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
			vertices.push_back(color.x);
			vertices.push_back(color.y);
			vertices.push_back(color.z);
			vertices.push_back(p2[0]);
			vertices.push_back(p2[1]);
			vertices.push_back(p2[2]);
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
			vertices.push_back(color.x);
			vertices.push_back(color.y);
			vertices.push_back(color.z);
			vertices.push_back(p3[0]);
			vertices.push_back(p3[1]);
			vertices.push_back(p3[2]);
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
			vertices.push_back(color.x);
			vertices.push_back(color.y);
			vertices.push_back(color.z);

			indices.push_back(x*size*6 + i*6);
			indices.push_back(x*size*6 + i*6 + 1);
			indices.push_back(x*size*6 + i*6 + 2);
			indices.push_back(x*size*6 + i*6 + 3);
			indices.push_back(x*size*6 + i*6 + 4);
			indices.push_back(x*size*6 + i*6 + 5);
		}
	}

	FAMesh *mesh = new FAMesh(vertices, indices, true, true);
	this->setMesh(*mesh);
	FAMaterial *material = new FAMaterial();
	glm::vec4 color = glm::vec4(1,1,2,1);
	// material->setColor(color);
	glm::vec3 direction = glm::vec3(1,1,0);
    glm::vec4 color_light = glm::vec4(1,1,1,1);
    float ambient = 0.5;
	material->setDirectionalLight(direction, color_light, ambient);
	this->setMaterial(*material);

	for (int i = 0; i < 50; ++i) {
		delete[] map[i];
	}
	delete[] map;

}

FATerrain::~FATerrain() {

}