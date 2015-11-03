#ifndef __First__FAGUITexturedPlane__
#define __First__FAGUITexturedPlane__

#include "FAGUIElement.h"
#include "FAMesh.h"
#include "FAShader.h"

class FAGUITexturedPlane : public FAGUIElement {
    
private:

    FAMesh *mesh;
    FAShader *shader;

    GLuint texture;
    GLint textureLocation;
    GLint positionLocation;
    GLint sizeLocation;
	
public:
    
    FAGUITexturedPlane();
    FAGUITexturedPlane(GLuint texture);

    void update(float dt);
    void render();

    ~FAGUITexturedPlane();

};

#endif