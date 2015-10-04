#ifndef __First__FAHUDTexturedPlane__
#define __First__FAHUDTexturedPlane__

#include "FAHUDElement.h"
#include "FAMesh.h"
#include "FAShader.h"

class FAHUDTexturedPlane : public FAHUDElement {
    
private:

    FAMesh *mesh;
    FAShader *shader;

    GLuint texture;
    GLint textureLocation;
    GLint positionLocation;
    GLint sizeLocation;
	
public:
    
    FAHUDTexturedPlane();
    FAHUDTexturedPlane(GLuint texture);

    void update(float dt);
    void render();

    ~FAHUDTexturedPlane();

};

#endif