#ifndef __First__FANode__
#define __First__FANode__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "FAAction.h"

#ifndef M_PI
#define M_PI 3.1415926536
#endif
#ifndef M_2PI
#define M_2PI 6.2831853072
#endif

class FAAction;

class FANode {
    bool isActive;

public:
	FANode();

	void addChild(FANode *child);
	std::vector<FANode *> getAllChildren();
    void setParent(FANode *parent);
    void removeFromParent();
    void removeChild(FANode *node);

    void update(float dt);
    virtual void render(){}

	void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 pos);
    void moveX(float x);
    void moveY(float y);
    void moveZ(float z);
    void move(glm::vec3 p);
    void setScale(float p);
    void setScale(glm::vec3 p);
    void setScale(float x, float y);
    void setRX(float rx);
    void setRY(float ry);
    void setRZ(float rz);
    void rotateX(float f);
    void rotateY(float f);
    void rotateZ(float f);
    void rotate(glm::vec3 r);
    
	float getX();
	float getY();
	float getZ();
    float getRX();
    float getRY();
    float getRZ();
	glm::vec3 getScale();
    glm::vec3 getPosition();
    glm::vec3 getRotation();

    void runAction(FAAction *action);

	virtual ~FANode();

protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
    glm::mat4 modelMatrix;
    std::vector<FANode *> children;
    FANode *parent = nullptr;
    FAAction *action = nullptr;

    virtual void onUpdate(float dt){}
    virtual void onRender(){}
};


#endif