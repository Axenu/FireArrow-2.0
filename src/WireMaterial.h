//
//  WireMaterial.hpp
//  FA
//
//  Created by Simon Nilsson on 4/1/16.
//  Copyright © 2016 Axenu. All rights reserved.
//

#ifndef WireMaterial_hpp
#define WireMaterial_hpp

#include <FA/FAMaterial.h>

class WireMaterial : public FAMaterial {
	
private:
	FAShader *shader;
	glm::mat4 viewProjectionMatrix;
	glm::mat4 modelMatrix;
	glm::vec4 color;
	
	GLint MVPLocation;
	GLint colorLocation;
	
public:
	WireMaterial();
	~WireMaterial();
	
	void bind();
	void setViewProjectionwMatrix(glm::mat4 &VPMatrix);
	void setModelMatrix(glm::mat4 &modelMatrix);
	void setColor(glm::vec4 color);
};

#endif /* WireMaterial_hpp */
