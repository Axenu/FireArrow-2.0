//
//  FAGUIButton.cpp
//  FA
//
//  Created by Simon Nilsson on 12/10/15.
//  Copyright © 2015 Axenu. All rights reserved.
//

#include <FA/FAGUIButton.h>

FAGUIButton::FAGUIButton() {
	FAFont * font = new FAFont("helveticaneue-light-webfont.ttf", 20);
	background = new FAGUIPlane();
	background->setHeight(0.1);
	background->setWidth(0.18);
	addChild(background);
	
	label = new FAGUILabel(font);
	label->setY(0.025);
	label->setX(0.025);
	addChild(label);
}

FAGUIButton::FAGUIButton(FAFont *font) {
	background = new FAGUIPlane();
	background->setHeight(0.1);
	background->setWidth(0.18);
	addChild(background);
	
	label = new FAGUILabel(font);
	label->setY(0.025);
	label->setX(0.025);
	addChild(label);
}

void FAGUIButton::setText(std::string s) {
	this->label->setText(s);
}

FAGUIButton::~FAGUIButton() {
	
}