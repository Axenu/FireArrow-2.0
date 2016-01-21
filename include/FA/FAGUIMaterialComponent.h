#ifndef __First__FAGUIMaterialComponent__
#define __First__FAGUIMaterialComponent__

#include "FAGUIPlane.h"

class FAGUIMaterialComponent : public FAGUIElement {
    
private:
    std::string name;

//    FAFont *font;
//	FAGUIPlane *background;


public:
    
    FAGUIMaterialComponent();

    // virtual void onUpdate(float dt);
    // virtual void onRender();

    ~FAGUIMaterialComponent();

};

#endif