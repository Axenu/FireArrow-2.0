#ifndef __First__FAGUILabel__
#define __First__FAGUILabel__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include "FAFont.h"
#include "FAGUIElement.h"
#include "FAMesh.h"
#include "FAShader.h"

class FAGUILabel : public FAGUIElement {
    
private:

    FAMesh *mesh;
    FAFont *font;
    FAShader *shader;

    GLint positionLocation;
    GLint sizeLocation;

    std::string text = "Label";
	
public:
    
    FAGUILabel();
    FAGUILabel(FAFont *font);

    void setText(std::string text);

    std::string getText();

    void onUpdate(float dt);

    void renderCharacter(int character, float x, float y, float charWidth, float charHeigth);
    virtual void onRender();

    ~FAGUILabel();

    //debug
    void updateShader();
};

#endif