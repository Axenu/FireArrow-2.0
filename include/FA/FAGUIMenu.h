#ifndef FAGUIMenu_h
#define FAGUIMenu_h

#include "FAGUIPlane.h"
#include "FAGUILabel.h"
//#include "FAGUILabel.h"

class FAGUIMenu : public FAGUIElement {
	
private:
	FAGUIPlane *background;
	glm::vec4 margin;
//	float width;
//	FAGUILabel *label;
	FAFont *font;
	
public:
	
	FAGUIMenu();
	FAGUIMenu(FAFont *font);
	
//	void setText(std::string s);
	
	void addLabel(std::string text);
	
	~FAGUIMenu();
	
};

#endif