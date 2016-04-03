#ifndef __First__FAGUILabel__
#define __First__FAGUILabel__

#include "FAFont.h"
#include "FAGUIElement.h"
#include "FAMesh.h"
#include "FAShader.h"

class FAGUILabel : public FAGUIElement {
    
private:

    GLint positionLocation;
	
	GLuint VBO = 0;
	GLuint EBO = 0;
	GLuint VAO = 0;
	
	long verticesSize;
	long indicesSize;

    std::string text = "Label";
	
public:
    
    FAGUILabel();
    FAGUILabel(FAFont *font);

    void setText(std::string text);
	
	float getWidth();

    std::string getText();

    void onUpdate(float dt);

    void renderCharacter(int character, float x, float y, float charWidth, float charHeigth);
    virtual void onRender();

    ~FAGUILabel();

    //debug
    void updateShader();
protected:

    FAMesh *mesh;
    FAFont *font;
    FAShader *shader;
};

#endif