#ifndef __First__FAGUIPlane__
#define __First__FAGUIPlane__

#include "FAGUIElement.h"
#include "FAMesh.h"
#include "FAShader.h"

class FAGUIPlane : public FAGUIElement {
    
private:

    FAMesh *mesh;
    FAShader *shader;

    glm::vec4 color;

    GLint colorLocation;
    GLint positionLocation;
    GLint sizeLocation;
	
public:
    
    FAGUIPlane();

    virtual void onUpdate(float dt);
    virtual void onRender();

    ~FAGUIPlane();

};

#endif