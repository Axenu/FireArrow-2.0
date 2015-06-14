#ifndef __First__FAText__
#define __First__FAText__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include "FAFont.h"
#include "FAHUDElement.h"
#include "FAMesh.h"
#include "FAShader.h"

class FAText : public FAHUDElement {
    
private:

    FAMesh *mesh;
    FAFont *font;
    FAShader *shader;

    GLint positionLocation;
    GLint sizeLocation;

    std::string text;
	
public:
    
    FAText();
    FAText(FAFont *font);

    void setText(std::string text);

    std::string getText();

    void update(float dt);

    void renderCharacter(int character, float x, float y, float charWidth, float charHeigth);
    void render();

    ~FAText();

    //debug
    void updateShader();
};

#endif