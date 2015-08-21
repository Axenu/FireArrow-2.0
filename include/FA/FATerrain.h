#ifndef __FireArrow__FATerrain__
#define __FireArrow__FATerrain__

#include <FA/FAModel.h>
#include <iostream>
#include <stdlib.h>
#include <time.h> 

class FATerrain : public FAModel {

private:

	void generateHeightMap();

public:
	FATerrain();



	~FATerrain();
	
};

#endif