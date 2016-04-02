#include <FA/FAQuadTree.h>

FAQuadTree::FAQuadTree() {
	this->nodes = new FAQuadTree*[4];
	nodes[0] = nullptr;
	nodes[1] = nullptr;
	nodes[2] = nullptr;
	nodes[3] = nullptr;
}

FAQuadTree::FAQuadTree(int level, const FAAABB &bounds) : FAQuadTree() {
	this->level = level;
	this->bounds = bounds;
}

void FAQuadTree::split() {
	FAAABB bound = FAAABB(this->bounds.center, this->bounds.half);
	bound.half.x *= 0.5;
	bound.half.z *= 0.5;
	bound.center.x += bound.half.x;
	bound.center.z += bound.half.z;
	nodes[0] = new FAQuadTree(this->level+1,bound);
	bound.center.x -= bound.half.x * 2;
	nodes[1] = new FAQuadTree(this->level+1,bound);
	bound.center.z -= bound.half.z * 2;
	nodes[2] = new FAQuadTree(this->level+1,bound);
	bound.center.x += bound.half.x * 2;
	nodes[3] = new FAQuadTree(this->level+1,bound);
}

int FAQuadTree::getIndex(const FAAABB &other) {
	
//	//right side
//	if (other.globalCenter.x - other.half.x > this->bounds.center.x) {
//		//top quad
//		if (other.globalCenter.z - other.half.z > this->bounds.center.z) {
//			return 0;
//		} else if (other.globalCenter.z + other.half.z < this->bounds.center.z) {
//			return 3;
//		}
//	} else if (other.globalCenter.x + other.half.x < this->bounds.center.x) {
//		//top quad
//		if (other.globalCenter.z - other.half.z > this->bounds.center.z) {
//			return 1;
//		} else if (other.globalCenter.z + other.half.z < this->bounds.center.z) {
//			return 2;
//		}
//	}
//	return -1;
	
	//right side
	if (other.globalCenter.x > this->bounds.center.x) {
		//top quad
		if (other.globalCenter.z > this->bounds.center.z) {
			return 0;
		} else if (other.globalCenter.z < this->bounds.center.z) {
			return 3;
		}
	} else if (other.globalCenter.x < this->bounds.center.x) {
		//top quad
		if (other.globalCenter.z > this->bounds.center.z) {
			return 1;
		//bottom quad
		} else if (other.globalCenter.z < this->bounds.center.z) {
			return 2;
		}
	}
	return -1;
}

void FAQuadTree::insert(FAModel *other) {
	if (nodes[0] != nullptr) {
		int index = getIndex(other->getBounds());
		if (index != -1) {
			nodes[index]->insert(other);
			return;
		}
	}
	subNodes.push_back(other);
	//should expand?
	if (subNodes.size() > maxSubNodes && level < maxLevels) {
		if (nodes[0] == nullptr) {
			split();
		}
		for (int i = 0; i < subNodes.size(); i++) {
			int index = getIndex(subNodes[i]->getBounds());
			if (index != -1) {
				nodes[index]->insert(subNodes[i]);
				subNodes.erase(subNodes.begin() + i);
				i--;
			}
		}
	}
}

std::vector<FAModel *> FAQuadTree::cull(FACamera *cam) {
	std::vector<FAModel *> models;
	//improve test A LOT
	if (cam->boundingVolume->collideWith(this->bounds)) {
//	if (level < 2) {
		this->ma->setColor(glm::vec4(1,0,0,1));
		if (nodes[0] != nullptr) {
			for (int i = 0; i < 4; i++) {
				std::vector<FAModel *> temp = nodes[i]->cull(cam);
				models.insert(models.end(), temp.begin(), temp.end());
			}

		}
		//test if children inside
		for (int i = 0; i < subNodes.size(); i++) {
			models.push_back(subNodes[i]);
		}
	} else {
		this->ma->setColor(glm::vec4(0,0,0,0));
	}
	
	return models;
}

std::vector<FAModel *> FAQuadTree::getWireMeshes() {
	std::vector<FAModel *> mesches;
	ma = new WireMaterial();
	//set color;
	glm::vec4 color = glm::vec4(0,0,0,0);
//	if (level == 0) {
//		color = glm::vec3(1,1,0);
//	} else if (level == 1) {
//		color = glm::vec3(1,0,1);
//	} else if (level == 2) {
//		color = glm::vec3(0,1,1);
//	} else if (level == 3) {
//		color = glm::vec3(0,1,0);
//	} else {
//		color = glm::vec3(0,0,1);
//	}
	ma->setColor(color);
	FAMesh *m;
	FAModel *model;
	if (this->nodes[0] != nullptr) {
		for (int i = 0; i < 4; i++) {
			std::vector<FAModel *> temp = this->nodes[i]->getWireMeshes();
			mesches.insert(mesches.end(), temp.begin(), temp.end());
		}
	}
	this->bounds.calculateMesh();
	m = new FAMesh(this->bounds.getVertices(), this->bounds.getIndices(), false, false);
	m->renderMode = GL_LINES;
	model = new FAModel(m, ma);
//	model->setPosition(this->bounds.center);
	mesches.push_back(model);
	return mesches;
}

FAQuadTree::~FAQuadTree() {
	
}