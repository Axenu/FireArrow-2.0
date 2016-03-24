#ifndef __First__FAGaussianRenderPass__
#define __First__FAGaussianRenderPass__

#include <FA/FARenderPass.h>
#include <FA/FAShader.h>
#include <FA/FAmesh.h>

class FAGaussianRenderPass : public FARenderPass {
	
private:
	
	GLint renderedTexture;
	FAMesh *squareMesh;
	FAShader *horizontalPass;
	FAShader *verticalPass;
	
	GLint horizontalTextureLocation;
	GLint horizontalResolutionLocation;
	GLint verticalTextureLocation;
	GLint verticalResolutionLocation;
	GLuint fboTexture;
	GLuint fbo;
	
	glm::vec2 resolution;
	
	
public:
	FAGaussianRenderPass();
	~FAGaussianRenderPass();
	
	void render();
	
	void finalize();
	
	void setRenderdTexture(GLint texture);
	
};

#endif 
