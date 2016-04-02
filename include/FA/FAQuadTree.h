#ifndef __First__FAQuadTree__
#define __First__FAQuadTree__

#include "FAModel.h"
#include "FAAABB.h"
#include "FACamera.h"

//debugg
#include "WireMaterial.h"

class FAQuadTree {
private:
	
	const int maxSubNodes = 10;
	const int maxLevels = 5;
	
	int level;
	std::vector<FAModel *> subNodes;
	FAAABB bounds;
	FAQuadTree **nodes;
	//debug
	WireMaterial *ma;
	
public:
	FAQuadTree();
	FAQuadTree(int level, const FAAABB &bounds);
	
	void split();
	int getIndex(const FAAABB &other);
	void insert(FAModel *other);
	std::vector<FAModel *> cull(FACamera *cam);
	
	std::vector<FAModel *> getWireMeshes();
	
	
	~FAQuadTree();
};

#endif
