#ifndef __First__FAMainRenderPass__
#define __First__FAMainRenderPass__

#include <FA/FARenderPass.h>

class FAMainRenderPass : public FARenderPass {

private:

public:
	FAMainRenderPass();
	~FAMainRenderPass();

	void render();
	
};

#endif