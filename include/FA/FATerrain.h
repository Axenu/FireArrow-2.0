#ifndef __FireArrow__FATerrain__
#define __FireArrow__FATerrain__

#include <FA/FATerrainChunk.h>
#include <iostream>
#include <stdlib.h>
#include <time.h> 

class FATerrain : public FAMesh {

private:

	void generateHeightMap();
	int chunkSize;
	int tileSize;
	float heightMapSize;
	float **heightMap;

public:
	FATerrain();



	~FATerrain();
	
};

#endif