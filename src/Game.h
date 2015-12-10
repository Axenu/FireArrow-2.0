#ifndef __First__FAGame__
#define __First__FAGame__

#include <FA/FAEngine.h>
#include "testScene.h"

class Game : public FAEngine {

private:
	
public:
    Game();
    
    
    void setWindowAttributes();
    
    ~Game();
    
protected:
    void init();
    FAScene* setInitialScene();
};

#endif