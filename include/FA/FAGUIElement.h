#ifndef __First__FAGUIElement__
#define __First__FAGUIElement__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "iostream"
#include "FANode.h"

// #define FAPOSITION_MODE_ABSOLUT 0
// #define FAPOSITION_MODE_RELATIVE 1

class FAGUIElement {
    
private:

public:
    
    FAGUIElement();

    void addChild(FAGUIElement *child);
    
    void update(float dt);
    void update(float dt, glm::vec2 transformation);
    void render();

    void setID(int id);
    void setX(float x);
    void setY(float y);
    void setPosition(float x, float y);
    void setPosition(glm::vec2 pos);
    void moveX(float x);
    void moveY(float y);
    void move(glm::vec2 p);
    //percentage of screen size
    void setSize(float p);
    void setSize(glm::vec2 p);
    void setSize(float x, float y);
    void setWidth(float width);
    void setHeight(float height);
	
	float getX();
	float getY();
	glm::vec2 getSize();
	float getWidth();
	float getHeight();

    int getID();

    ~FAGUIElement();

protected:
	
	int identity;
	bool isClickable;
    glm::vec2 globalTransformation;

    glm::vec2 size;
    glm::vec2 position;

    std::vector<FAGUIElement *> children;
    
    virtual void onUpdate(float dt){}
    virtual void onRender(){}

};

#endif