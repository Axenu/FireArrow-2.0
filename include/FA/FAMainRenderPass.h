#ifndef __First__FAMainRenderPass__
#define __First__FAMainRenderPass__

#include <FA/FARenderPass.h>

class FAMainRenderPass : public FARenderPass {

private:

	GLuint fbo;
	GLuint fboTexture;
	
	bool _hasFBO;
	
public:
	FAMainRenderPass();
	~FAMainRenderPass();

	void render();
	
	void enablePostProcessing();
	void disablePostProsessing();
	
	GLint getFBOTexture();
	
};

#endif