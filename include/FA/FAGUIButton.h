//
//  FAGUIButton.h
//  FA
//
//  Created by Simon Nilsson on 12/10/15.
//  Copyright © 2015 Axenu. All rights reserved.
//

#ifndef __First__FAGUIButton__
#define __First__FAGUIButton__

#include "FAGUIPlane.h"
#include "FAGUILabel.h"

class FAGUIButton : public FAGUIElement {
	
private:
	FAGUIPlane *background;
	FAGUILabel *label;
	
public:
	
	FAGUIButton();
	FAGUIButton(FAFont *font);
	
	void cursorPress();
	void cursorRelease();
	void cursorEnter();
	void cursorLeave();
	
	void setText(std::string s);
	
	~FAGUIButton();
	
};


#endif /* FAGUIButton_h */
