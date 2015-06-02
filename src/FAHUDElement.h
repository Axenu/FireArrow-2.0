#ifndef __First__FAHUDElement__
#define __First__FAHUDElement__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

// #define FAPOSITION_MODE_ABSOLUT 0
// #define FAPOSITION_MODE_RELATIVE 1

class FAHUDElement {
    
private:

public:
    
    FAHUDElement();

    void setID(int id);
    void setPosition(glm::vec3 position);
    void setPosition(float x, float y, float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setSize(float width, float height);
    void setWidth(float width);
    void setHeight(float height);
    
    int getID();
    void onUpdate();
    void onRender();

    ~FAHUDElement();

protected:
	
	int identity;
	float width;
	float height;
	glm::vec3 position;
	bool isClickable;

	virtual void update(float dt) = 0;
	virtual void render() = 0;
};

#endif