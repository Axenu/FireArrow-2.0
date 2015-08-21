#ifndef __First__FAModel__
#define __First__FAModel__

#include <iostream>
#include "FAMesh.h"
#include "FAMaterial.h"
#include "FACamera.h"
#include "FANode.h"

class FAModel : public FANode {

private:
	FAMesh mesh;
	FAMaterial material;
public:
	FAModel();
	FAModel(FAMesh &mesh);
	FAModel(FAMesh &mesh, FAMaterial &material);

	void setMaterial(FAMaterial &material);
	void setMesh(FAMesh &mesh);
	void setMesh(std::string path);

	FAMaterial &getMaterial();
	const FAMesh &getMesh() const;
	glm::mat4 &getModelMatrix();

	virtual void onUpdate(float dt);

	~FAModel();
	
};

#endif