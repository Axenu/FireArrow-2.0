#ifndef __FireArrow__FARenderPasscallbackInterface__
#define __FireArrow__FARenderPasscallbackInterface__

#include <vector>
#include <FA/FAModel.h>

class FARenderPasscallbackInterface {
public:
	virtual std::vector<FAModel *> *getModels() = 0;
	virtual FACamera *getCamera() = 0;
	virtual float getWindowWidths() = 0;
};

#endif