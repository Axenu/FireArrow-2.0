#include <FA/FAMainRenderPass.h>

FAMainRenderPass::FAMainRenderPass() {

    this->priority = 0;
    this->name = "Main";
	this->_hasFBO = false;
}

FAMainRenderPass::~FAMainRenderPass() {
	glDeleteTextures(1, &fboTexture);
	glDeleteFramebuffers(1, &fbo);
}


void FAMainRenderPass::render() {
	// std::cout << "renderMain" << std::endl;
	if (_hasFBO) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
		glClearColor(0.5,0.5,0.5,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}
	if (parent != nullptr) {
		// std::vector<FAModel *> *mo = parent->getModels();
		// glm::mat4 &m = parent->getWindowWidth() << std::endl;
		// std::cout << parent->getModels()->size() << std::endl;
		parent->getCullCamera()->useView();
		parent->cullModels(parent->getCullCamera());
		for (FAModel *m : *parent->getModels()) {
			m->getMaterial().setViewProjectionwMatrix(parent->getCamera()->VPMatrix);
			m->getMaterial().setModelMatrix(m->getModelMatrix());
			m->getMaterial().bind();
			m->getMesh().render();
		}
	}
	if (_hasFBO)
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void FAMainRenderPass::enablePostProcessing() {
	this->_hasFBO = true;
	glGenTextures(1, &fboTexture);
	glBindTexture(GL_TEXTURE_2D, fboTexture);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->windowWidth, this->windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->windowWidth, this->windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
	
	
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);

	
	GLenum fboStatus;
	fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Creating framebuffer failed with code: " << fboStatus << std::endl;
		switch (fboStatus)
		{
			case GL_FRAMEBUFFER_UNDEFINED:
				// print("No window?");
				// Oops, no window exists?
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				// print("Incomplete attachment");
				// Check the status of each attachment
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				// print("No buffers!");
				// Attach at least one buffer to the FBO
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				// print("Incomplete draw buffer");
				// Check that all attachments enabled via
				// glDrawBuffers exist in FBO
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				// print("No read buffer!");
				// Check that the buffer specified via // glReadBuffer exists in FBO
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
				// print("Unsuported");
				// Reconsider formats used for attached buffers break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				// print("Incomplete multisample!");
				// Make sure the number of samples for each // attachment is the same
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				// print("Incorrect number of layers!");
				// Make sure the number of layers for each // attachment is the same
				break;
		}
	}
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void FAMainRenderPass::disablePostProsessing() {
	this->_hasFBO = false;
	//remove fbo
	glDeleteFramebuffers(1, &fbo);
}

GLint FAMainRenderPass::getFBOTexture() {
	return fboTexture;
}

