#include <FA/FAGUIMenu.h>

FAGUIMenu::FAGUIMenu() {
	this->size.x = 0.3;
	this->size.y = 0.3;
	
	background = new FAGUIPlane();
	background->setHeight(this->size.y);
	background->setWidth(this->size.x);
//	background->setPosition(0.5, 0.5);
	addChild(background);
	
}

FAGUIMenu::FAGUIMenu(FAFont *font) {
	this->size.x = 0.3;
	this->size.y = 0.0;
	this->position.x = 0.5;
	this->position.y = 0.5;
	this->font = font;
	this->margin = glm::vec4(0.005);
	
	background = new FAGUIPlane();
	background->setHeight(this->size.y);
	background->setWidth(this->size.x);
	background->setPosition(0,0);
	addChild(background);
}

void FAGUIMenu::addLabel(std::string text) {
	
	FAGUILabel *label = new FAGUILabel(font);
	label->setText(text);
	label->setY(margin.y - this->getHeight());
	label->setX(margin.x);
	addChild(label);
	
	this->background->setY(-this->size.y);
	this->size.y += label->getHeight()/4.0;
	this->background->setSize(this->size);

}
//


FAGUIMenu::~FAGUIMenu() {
	
}