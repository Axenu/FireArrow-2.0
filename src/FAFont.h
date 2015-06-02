#ifndef __First__FAFont__
#define __First__FAFont__

#define GLFW_INCLUDE_GLCOREARB

#include <ft2build.h>
#include <freetype.h>
#include <iostream>
#include <fstream>
#include <GLFW/glfw3.h>

class FAFont {
    
private:
    float fontSize;
	float fontHeight;
	
public:
    uint windowWidth;
    uint windowHeight;
    GLuint texture[256];
    FT_Face face;
    
    FAFont();
    FAFont(std::string path, const int _fontSize);
	FAFont(std::string path, const int _fontSize, uint _windowWidth, uint _windowHeight);
    ~FAFont();
    void loadCharacters();
	
	float getFontSize();

	// float getFontHeight();
};

#endif