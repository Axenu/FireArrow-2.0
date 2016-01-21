#ifndef __First__FAFont__
#define __First__FAFont__

#define GLFW_INCLUDE_GLCOREARB

#include <ft2build.h>
#include <freetype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <GLFW/glfw3.h>

struct glyph {
	int x, y;
	int width, height;
	int xOffset, yOffset;
	int xAdvance;
};

class FAFont {
    
private:
    float fontSize;
	float fontHeight;
	GLuint textureAtlas;
	int textureWidth;
	int textureHeight;
	
	std::map<int, glyph> glyphs;
	
public:
    uint windowWidth;
    uint windowHeight;
    GLuint texture[256];
    FT_Face face;
    
    FAFont();
	FAFont(std::string path);
    FAFont(std::string path, const int _fontSize);
	FAFont(std::string path, const int _fontSize, uint _windowWidth, uint _windowHeight);
    ~FAFont();
    void loadCharacters();
	
	float getFontSize();
	float getWidthOfString(std::string s);

	// float getFontHeight();
};

#endif