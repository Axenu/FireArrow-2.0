#include <FA/FACSMRenderPass.h>

FACSMRenderPass::FACSMRenderPass() {
	int shadowMapWidth = 1024;
    int shadowMapHeight = 720;
    this->priority = -3;
    this->name = "CSM";
    
    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMap);
    
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, frustums, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameterf( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameterf( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    glGenFramebuffers(1, &shadowFbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, shadowFbo);
    glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0, 0);
    glDrawBuffers(0, NULL);
    
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

    shader = new FAShader("shadow");

    glUseProgram(shader->shaderProgram);

    modelMatrixLocation = glGetUniformLocation(shader->shaderProgram, "modelMatrix");
    viewProjectionMatrixLocation = glGetUniformLocation(shader->shaderProgram, "viewProjectionMatrix");
    glUseProgram(0);

    if (modelMatrixLocation == -1) 
        std::cout << "Error getting uniform modelMatrixLocation" << std::endl;
    if (viewProjectionMatrixLocation == -1) 
        std::cout << "Error getting uniform viewProjectionMatrixLocation" << std::endl;

    inverseShadowMatrix = new glm::mat4[frustums];

}


void FACSMRenderPass::render() {
	// std::cout << "renderCSM" << std::endl;
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    // glEnable(GL_CULL_FACE);
    // glViewport(0,0,this->windowWidth,this->windowHeight);
    glm::mat4 *shadowMatrix = new glm::mat4[frustums];
    shadowMatrix[0] = calculateShadowCamera(0, 4);
    shadowMatrix[1] = calculateShadowCamera(4, 12);
    shadowMatrix[2] = calculateShadowCamera(12, 30);
    shadowMatrix[3] = calculateShadowCamera(30, 100);
    for (int i = 0; i < frustums; i++) {
        // std::cout << shadowMap << std::endl;
        //        shadowMatrix.push_back(calculateShadowCamera(0,100));
        // inverseShadowMatrix[i] = glm::mat4();
        inverseShadowMatrix[i] = glm::translate(glm::mat4(), glm::vec3(0.5,0.5,0.5));
        inverseShadowMatrix[i] = glm::scale(inverseShadowMatrix[i], glm::vec3(0.5,0.5,0.5));
        inverseShadowMatrix[i] = inverseShadowMatrix[i] * shadowMatrix[i];
        glBindFramebuffer(GL_FRAMEBUFFER, shadowFbo);
        glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0, GLint(i));
        
        glClear(GL_DEPTH_BUFFER_BIT);
        
        // glCullFace(GL_FRONT);

        glUseProgram(shader->shaderProgram);
		

        for (FAModel *m : *parent->getModels()) {
			// m->getMaterial().setViewProjectionwMatrix(&(parent->getCamera()->VPMatrix));
			// m->getMaterial().setModelMatrix(m->modelMatrix);
			// m->getMaterial().bind();
            glUniformMatrix4fv(viewProjectionMatrixLocation, 1, GL_FALSE, &shadowMatrix[i][0][0]);
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &m->getModelMatrix()[0][0]);
			m->getMesh().render();
		}
//        for(FANode *node : children)
//            node->renderShadow();
        // children->renderShadow(shadowMatrix[i]);
    }
    
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//    glViewport(0, 0, windowWidth*2, windowHeigth*2);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    
    //    glEnable(GL_POLYGON_OFFSET_FILL);
    //    glPolygonOffset(factor,units);
    
    // glCullFace(GL_BACK);
}

GLuint *FACSMRenderPass::getShadowMap() {
    return &this->shadowMap;
}

glm::mat4 *FACSMRenderPass::getInverseShadowMatrix() {
    return this->inverseShadowMatrix;
}

int *FACSMRenderPass::getFrustums() {
    return &this->frustums;
}

// -----------------(( private ))---------------------

// void FACSMRenderPass::

glm::mat4 FACSMRenderPass::calculateShadowCamera(float near, float far) {
	// testCamera->useView();
	glm::mat4 camViewMatrix = parent->getCamera()->getViewMatrix();
	float fieldOfView = parent->getCamera()->getFieldOfView();
	float aspectRatio = parent->getCamera()->getAspectRatio();
	glm::vec3 camPosition = parent->getCamera()->getPosition();

	glm::vec3 globalLightDirection = glm::vec3(1,-1,0);

    glm::vec3 cameraPoints[8];
    glm::vec3 cameraDirection = glm::normalize(glm::vec3(-camViewMatrix[0][2],-camViewMatrix[1][2],-camViewMatrix[2][2]));
    glm::vec3 up = glm::normalize(glm::vec3(camViewMatrix[0][1],camViewMatrix[1][1],camViewMatrix[2][1]));
    glm::vec3 cameraRightVector = glm::normalize(glm::cross(up, cameraDirection));
    
    //setup variables for calculating camerabounds
    float tan = 2 * tanf(fieldOfView * glm::pi<float>() / 360.0);
    float heightNear = tan * near;
    float heightFar = tan * far;
    
    float widthNear = heightNear * aspectRatio;
    float widthFar = heightFar * aspectRatio;

    glm::vec3 centerNear = camPosition + cameraDirection * near;
    glm::vec3 centerFar = camPosition + cameraDirection * far;
    
    //calculate camera bounds
    cameraPoints[0] = centerNear + (up * (heightNear/2)) - (cameraRightVector * (widthNear/2));
    cameraPoints[1] = centerNear + (up * (heightNear/2)) + (cameraRightVector * (widthNear/2));
    cameraPoints[2] = centerNear - (up * (heightNear/2)) - (cameraRightVector * (widthNear/2));
    cameraPoints[3] = centerNear - (up * (heightNear/2)) + (cameraRightVector * (widthNear/2));
    cameraPoints[4] = centerFar + (up * (heightFar/2)) - (cameraRightVector * (widthFar/2));
    cameraPoints[5] = centerFar + (up * (heightFar/2)) + (cameraRightVector * (widthFar/2));
    cameraPoints[6] = centerFar - (up * (heightFar/2)) - (cameraRightVector * (widthFar/2));
    cameraPoints[7] = centerFar - (up * (heightFar/2)) + (cameraRightVector * (widthFar/2));
    
    glm::vec3 rightLeftNormal = glm::normalize(glm::cross(glm::vec3(0,1,0), globalLightDirection));
    glm::vec3 topBottomNormal = glm::normalize(glm::cross(rightLeftNormal, globalLightDirection));
    
    float furthestPoint = glm::dot(globalLightDirection, cameraPoints[0]);
    float closestPoint = furthestPoint;
    
    float rightPoint = glm::dot(rightLeftNormal, cameraPoints[0]);
    float leftPoint = rightPoint;
    
    float topPoint = glm::dot(topBottomNormal, cameraPoints[0]);
    float bottomPoint = topPoint;
    
    glm::vec3 closest = cameraPoints[0];
    glm::vec3 furthest = closest;
    glm::vec3 right = closest;
    glm::vec3 left = closest;
    glm::vec3 top = closest;
    glm::vec3 bottom = closest;
    
    
    for (int i = 1; i < 8; i++) {
        float p = glm::dot(globalLightDirection, cameraPoints[i]);
        if (p > furthestPoint) {
            furthestPoint = p;
            furthest = cameraPoints[i];
        }
        if (p < closestPoint) {
            closestPoint = p;
            closest = cameraPoints[i];
        }
        p = glm::dot(rightLeftNormal, cameraPoints[i]);
        if (p > rightPoint) {
            rightPoint = p;
            right = cameraPoints[i];
        }
        if (p < leftPoint) {
            leftPoint = p;
            left = cameraPoints[i];
        }
        p = glm::dot(topBottomNormal, cameraPoints[i]);
        if (p > topPoint) {
            topPoint = p;
            top = cameraPoints[i];
        }
        if (p < bottomPoint) {
            bottomPoint = p;
            bottom = cameraPoints[i];
        }
    }
    
    float width = glm::abs(rightPoint - leftPoint)/2.0f;
    glm::vec3 middleRightLeft = (right + left)/2.0f;
    float height = glm::abs(topPoint - bottomPoint)/2.0f;
    glm::vec3 middletopBottom = (top + bottom)/2.0f;
    
    
    float d[3];
    d[0] = glm::dot(globalLightDirection, closest);
    d[1] = glm::dot(rightLeftNormal, middleRightLeft);
    d[2] = glm::dot(topBottomNormal, middletopBottom);
    float farPlane = glm::abs(furthestPoint - closestPoint);
    
    glm::mat3 equations = glm::mat3(globalLightDirection.x, rightLeftNormal.x, topBottomNormal.x, globalLightDirection.y,rightLeftNormal.y, topBottomNormal.y, globalLightDirection.z, rightLeftNormal.z, topBottomNormal.z);
    glm::mat3 solution = glm::inverse(equations);
    glm::vec3 finalPoint = solution * glm::vec3(d[0],d[1],d[2]);
    glm::mat4 projectionMatrix = glm::ortho(-width, width, -height, height, -100.0f, farPlane);
    glm::mat4 viewMatrix = glm::lookAt(finalPoint, finalPoint + globalLightDirection, glm::vec3(0,1,0));
    
    // calculate corners of frustum
    //not nessesary!
    // if (isWireFrames) {
    //     wireFrame->SetModel(cameraPoints);
    //     glm::vec3 corners[8];
    //     glm::vec4 planes[6];
    //     planes[0] = glm::vec4(globalLightDirection.x, globalLightDirection.y, globalLightDirection.z, glm::dot(globalLightDirection, closest));
    //     planes[1] = glm::vec4(globalLightDirection.x, globalLightDirection.y, globalLightDirection.z, glm::dot(globalLightDirection, furthest));
    //     planes[2] = glm::vec4(rightLeftNormal.x, rightLeftNormal.y, rightLeftNormal.z, glm::dot(rightLeftNormal, left));
    //     planes[3] = glm::vec4(rightLeftNormal.x, rightLeftNormal.y, rightLeftNormal.z, glm::dot(rightLeftNormal, right));
    //     planes[4] = glm::vec4(topBottomNormal.x, topBottomNormal.y, topBottomNormal.z, glm::dot(topBottomNormal, top));
    //     planes[5] = glm::vec4(topBottomNormal.x, topBottomNormal.y, topBottomNormal.z, glm::dot(topBottomNormal, bottom));
        
    //     corners[0] = intersectionBetweenThreePlanes(planes[0], planes[2], planes[4]);
    //     corners[1] = intersectionBetweenThreePlanes(planes[0], planes[2], planes[5]);
    //     corners[2] = intersectionBetweenThreePlanes(planes[0], planes[3], planes[4]);
    //     corners[3] = intersectionBetweenThreePlanes(planes[0], planes[3], planes[5]);
    //     corners[4] = intersectionBetweenThreePlanes(planes[1], planes[2], planes[4]);
    //     corners[5] = intersectionBetweenThreePlanes(planes[1], planes[2], planes[5]);
    //     corners[6] = intersectionBetweenThreePlanes(planes[1], planes[3], planes[4]);
    //     corners[7] = intersectionBetweenThreePlanes(planes[1], planes[3], planes[5]);
    //     shadowWireFrame->SetModel(corners);
    // }

    return projectionMatrix * viewMatrix;
}

// glm::vec3 FACSMRenderPass::intersectionBetweenThreePlanes(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3) {
    
//     glm::mat3 equations = glm::mat3(p1.x, p2.x, p3.x, p1.y, p2.y, p3.y, p1.z, p2.z, p3.z);
//     glm::mat3 solution = glm::inverse(equations);
	
//     return solution * glm::vec3(p1.w,p2.w,p3.w);
// }