#include <FA/FAShadowMapRenderPass.h>

FAShadowMapRenderPass::FAShadowMapRenderPass() {
	int shadowMapWidth = 2560;
    int shadowMapHeight = 1440;
    this->priority = -3;
    this->name = "ShadowMap";
    
    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &shadowFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFbo);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
    // glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0, 0);
    // glDrawBuffers(0, NULL);
    
    GLenum fboStatus;
    fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Creating shadow framebuffer failed with code: " << fboStatus << std::endl;
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

    // std::string vert = "#version 400 core\nuniform mat4 viewProjectionMatrix;uniform mat4 modelMatrix;layout(location = 0) in vec3 in_Position;void main() {gl_Position = viewProjectionMatrix * modelMatrix * vec4(in_Position, 1.0);}";
    // std::string frag = "#version 400 core\nvoid main() {}";
    shader = new FAShader("shadow");
    shader->printListOfUniforms();

    glUseProgram(shader->shaderProgram);

    modelMatrixLocation = glGetUniformLocation(shader->shaderProgram, "MVPMatrix");
    glUseProgram(0);

    if (modelMatrixLocation == -1) 
        std::cout << "Error getting uniform MVPMatrix" << std::endl;

}

FAShadowMapRenderPass::~FAShadowMapRenderPass() {
	
}

void FAShadowMapRenderPass::render() {
	// std::cout << "renderCSM" << std::endl;
    // glEnable(GL_CULL_FACE);
    // glViewport(0,0,this->windowWidth,this->windowHeight);
    glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);
 
    // Compute the MVP matrix from the light's point of view
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
    glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 depthModelMatrix = glm::mat4(1.0);
    glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFbo);
    // glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);
    
    glUseProgram(shader->shaderProgram);
    glViewport(0,0,2560,1440);
    glClear(GL_DEPTH_BUFFER_BIT);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    
    glCullFace(GL_FRONT);

    for (FAModel *m : *parent->getModels()) {
        glUniformMatrix4fv(viewProjectionMatrixLocation, 1, GL_FALSE, &depthMVP[0][0]);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &m->getModelMatrix()[0][0]);
		m->getMesh().render();
    }
    
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
   glViewport(0,0,2560,1440);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glCullFace(GL_BACK);
}

GLuint *FAShadowMapRenderPass::getShadowMap() {
    return &this->shadowMap;
}

glm::mat4 *FAShadowMapRenderPass::getInverseShadowMatrix() {
    return &this->inverseShadowMatrix;
}

//std::vector<FAMaterialComponent *> FAShadowMapRenderPass::getRequiredMaterialComponents() {
//	return std::vector<FAMaterialComponent *>();
//}