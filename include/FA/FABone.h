#ifndef __First__FABone__
#define __First__FABone__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <stdio.h>
#include <vector>
#include <string>

class FABone {
	
private:
	glm::vec3 position;
	glm::vec3 globalPosition;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 localMatrix, combinedMatrix;
	std::string name;
	FABone *parent;
	std::vector<FABone *> children;
	
public:
	FABone();
	FABone(std::string _name, glm::vec3 _position);
	
	void addChild(FABone *child);
	void setParent(FABone *_parent);
	void setGlobalPosition(glm::vec3 _position);
	void setPosition(glm::vec3 _position);
	void setRotation(glm::vec3 _rotation);
	void setScale(glm::vec3 _scale);
	void setName(std::string _name);
	void setLocalMatrix(glm::mat4 matrix);
	void setCombinedMatrix(glm::mat4 matrix);
	
	std::vector<FABone *> getChildren();
	FABone *getParent();
	glm::vec3 getGlobalPosition();
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();
	std::string getName();
	glm::mat4 getLocalMatrix();
	glm::mat4 getCombinedMatrix();
	
	~FABone();
};

#endif /* defined(__FireArrow__FABone__) */
