#include <FA/FAFont.h>

FAFont::FAFont() {
    
}

FAFont::FAFont(std::string path) {
	std::ifstream Stream(("/Users/Axenu/Developer/FireArrow 2.0/resources/fonts/" + path + ".fnt").c_str());
	std::string Line;
	std::string Read, Key, Value;
	std::size_t i;
	std::string textureFileName = "";
	
	float x = 0, y = 0;
	float width = 0, height = 0;
	float xOffset = 0, yOffset = 0;
//	float lineHeight = 0;
	
	while( !Stream.eof() )
	{
		std::stringstream LineStream;
		std::getline( Stream, Line );
		LineStream << Line;
		
		//read the line's type
		LineStream >> Read;
		if( Read == "common" ) {
//			std::cout << Line << std::endl;
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );
				
				//assign the correct value
				Converter << Value;
				if( Key == "scaleW" )
				{Converter >> textureWidth;}
				else if( Key == "scaleH" )
				{Converter >> textureHeight;
					fontHeight /= textureHeight;
				}
				else if( Key == "base" )
				{Converter >> baseline;}
				else if( Key == "file" )
				{Converter >> textureFileName;}
				else if( Key == "lineHeight" ) {
					Converter >> fontHeight;
				}
			}
		} else if( Read == "info" ) {
			//			std::cout << Line << std::endl;
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );
				
				//assign the correct value
				Converter << Value;
				if( Key == "size" )
				{Converter >> fontSize;}
			}
		} else if (Read == "char") {
//			std::cout << Line << std::endl;
			int charID = 0;
			glyph g;
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );
				
				//Assign the correct value
				Converter << Value;
				if( Key == "id" ) {
					Converter >> charID;
				} else if( Key == "x" ) {
					Converter >> x;
				} else if( Key == "y" ) {
					Converter >> y;
				} else if( Key == "width" ) {
					Converter >> width;
				} else if( Key == "height" ) {
					Converter >> height;
				} else if( Key == "xoffset" ) {
					Converter >> xOffset;
				} else if( Key == "yoffset" ) {
					Converter >> yOffset;
				} else if( Key == "xadvance" ) {
					Converter >> g.xAdvance;
				}
			}
			x /= textureWidth;
			y /= textureHeight;
			y = 1 - y;
			xOffset /= textureWidth;
			yOffset /= textureHeight;
			g.xAdvance /= (textureWidth * 2);
			width /= textureWidth;
			height /= textureHeight;
			yOffset = baseline/textureHeight - height - yOffset;
//			fontHeight /= textureHeight;
//			std::cout << fontHeight << std::endl;
			g.x1 = xOffset/2 - 1;
			g.x2 = (width + xOffset)/2 - 1;
			g.y1 = yOffset/2.0 - 1.0;// + fontHeight/2.0;
			g.y2 = (height + yOffset)/2.0 - 1.0;// + fontHeight/2.0;
			g.u1 = x;
			g.u2 = x + width;
			g.v1 = y - height;
			g.v2 = y;
			glyphs.insert(std::pair<int,glyph>(charID,g));
		}
	}
//	fontHeight /= textureHeight;
	fontSize /= textureHeight;
	fontTexture = FATexture::createTexture(("/Users/Axenu/Developer/FireArrow 2.0/resources/fonts/" + path + ".png").c_str());
	
}

FAFont::FAFont(std::string path, const int _fontSize) {
    this->fontSize = _fontSize * 10;
    this->windowWidth = 1024;
    this->windowHeight = 720;
    this->fontHeight = fontSize/windowHeight;

    FT_Library library;
    
    if(FT_Init_FreeType(&library)) {
        fprintf(stderr, "Could not init freetype library\n");
    }
    
    if(FT_New_Face(library, ("/Users/Axenu/Developer/FireArrow 2.0/resources/fonts/" + path).c_str(), 0, &face)) {
        fprintf(stderr, "Could not open font\n");
    }
    int error = FT_Set_Char_Size(face, 0, fontSize, windowWidth, windowHeight);
    
    if (error != 0) {
        std::cout << "error in FT_SET_PIXEL_SIZES wit code: " << error << std::endl;
    }
    
    loadCharacters();
}

FAFont::FAFont(std::string path, const int _fontSize, uint _windowWidth, uint _windowHeight) {
    this->fontSize = _fontSize * 10;
    this->windowWidth = _windowWidth;
    this->windowHeight = _windowHeight;
    this->fontHeight = fontSize/windowHeight;
    
    std::ifstream ifile("/Users/Axenu/Developer/FireArrow 2.0/resources/fonts/" + path);
    if (!ifile) {
        std::cout << "File does not exists!" << std::endl;
    }
    
    FT_Library library;
    
    if(FT_Init_FreeType(&library)) {
        fprintf(stderr, "Could not init freetype library\n");
    }

    int error = FT_New_Face(library, ("/Users/Axenu/Developer/FireArrow 2.0/resources/fonts/" + path).c_str(), 0, &face);
    if(error != 0) {
        std::cout << error << std::endl;
        fprintf(stderr, "Could not open font\n");
    }
    error = FT_Set_Char_Size(face, 0, fontSize, windowWidth * 2, windowHeight * 2);
    
    if (error != 0) {
        std::cout << "error in FT_SET_PIXEL_SIZES wit code: " << error << std::endl;
    }
    
    loadCharacters();
}

void FAFont::loadCharacters() {
    
    FT_GlyphSlot  slot = face->glyph;

    glGenTextures(128, &texture[0]);
    
    for (int i = 0; i < 128; i++) {

        FT_UInt glyph_index;

        glyph_index = FT_Get_Char_Index(face, i);
        
        int error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
        if ( error )
            std::cout << "Error loading glyph!" << std::endl;
        
        error = FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
        if ( error )
            std::cout << "Error rendering glyph!" << std::endl;

        glBindTexture(GL_TEXTURE_2D, texture[i]);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        glTexImage2D(
                     GL_TEXTURE_2D,
                     0,
                     GL_RED,
                     slot->bitmap.width,
                     slot->bitmap.rows,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     slot->bitmap.buffer
                     );

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}



float FAFont::getFontSize() {
    return fontSize;
}

float FAFont::getHeight() {
	return this->fontSize;
}

//float FAFont::getWidthOfString(std::string s) {
//	
//	return face->glyph->metrics.width;
//}

FAFont::~FAFont() {
    
}