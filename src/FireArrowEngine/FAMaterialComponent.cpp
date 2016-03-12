#include <FA/FAMaterialComponent.h>

FAMaterialComponent::FAMaterialComponent() {

}

FAMaterialComponent::~FAMaterialComponent() {

}

void FAMaterialComponent::setAttribute(std::string name, float value) {

}

std::string FAMaterialComponent::getVertexIO() {
	return this->vertexIO;
}

std::string FAMaterialComponent::getVertexMain() {
	return this->vertexMain;
}

std::string FAMaterialComponent::getFragmentIO() {
	return this->fragmentIO;
}

std::string FAMaterialComponent::getFragmentMain() {
	return this->fragmentMain;
}

std::string FAMaterialComponent::getFragmentMainOutput() {
	return this->fragmentOutput;
}

std::string FAMaterialComponent::getMaterialOutput() {
	return this->materialOutput;
}

std::string FAMaterialComponent::getLightOutput() {
	return this->lightOutput;
}

std::string FAMaterialComponent::getName() {
	return this->name;
}

std::vector<FAMaterialComponent *> *FAMaterialComponent::getRequirements() {
	return &this->requirements;
}

bool FAMaterialComponent::requiresModelData() {
	return this->modelData;
}

//Vertex position material

FAVertexPositionComponent::FAVertexPositionComponent() {
	vertexIO = "out vec4 pass_Position;\n";
	vertexMain = "pass_Position = MMatrix * vec4(in_Position.xyz, 1.0);\n";
	fragmentIO = "in vec4 pass_Position;\n";
	fragmentMain = "";
	name = "vertexPosition";
	modelData = true;
}

void FAVertexPositionComponent::setAttribute(std::string name, float value) {

}

void FAVertexPositionComponent::bind() {

}

void FAVertexPositionComponent::setUpLocations(GLint shaderProgram) {

}

//Vertex normal material

FAVertexNormalComponent::FAVertexNormalComponent() {
	vertexIO = "layout(location = 1) in vec3 in_Normal;\nout vec4 pass_Normal;\n";
	vertexMain = "pass_Normal = transpose(inverse(MMatrix)) * vec4(in_Normal, 0.0);\n";
	fragmentIO = "in vec4 pass_Normal;\n";
	fragmentMain = "";
	name = "vertexNormal";
	modelData = true;
}

void FAVertexNormalComponent::setAttribute(std::string name, float value) {

}

void FAVertexNormalComponent::bind() {

}

void FAVertexNormalComponent::setUpLocations(GLint shaderProgram) {

}

//Vertex Color material

FAVertexColorComponent::FAVertexColorComponent() {
	vertexIO = "layout(location = 2) in vec3 in_Color;\nout vec4 pass_Color;\n";
	vertexMain = "pass_Color = vec4(in_Color, 1.0);\n";
	fragmentIO = "in vec4 pass_Color;\n";
	fragmentMain = "";
	// fragmentOutput = "(OTHER_OUT) * pass_Color";
	materialOutput = " * pass_Color";
	name = "vertexColor";
	modelData = true;
}

void FAVertexColorComponent::setAttribute(std::string name, float value) {

}

void FAVertexColorComponent::bind() {

}

void FAVertexColorComponent::setUpLocations(GLint shaderProgram) {

}

//Vertex UV material

FAVertexUVComponent::FAVertexUVComponent() {
	vertexIO = "layout(location = 3) in vec2 in_UV;\nout vec2 pass_UV;\n";
	vertexMain = "pass_UV = in_UV;\n";
	fragmentIO = "in vec2 pass_UV;\n";
	fragmentMain = "";
	// fragmentOutput = "OTHER_OUT";
	name = "vertexUV";
	modelData = true;
}

void FAVertexUVComponent::setAttribute(std::string name, float value) {

}

void FAVertexUVComponent::bind() {

}

void FAVertexUVComponent::setUpLocations(GLint shaderProgram) {

}

//Directional light material

FADirectionalLightComponent::FADirectionalLightComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform vec4 diffuseColor;\nuniform vec3 direction;\n";
	fragmentMain = "vec4 light1 = max(dot(direction,pass_Normal.xyz), 0.0) * diffuseColor;\n";
	lightOutput = "light1";
	name = "Directional light";
	requirements.push_back(new FAVertexNormalComponent);
	modelData = false;
}

void FADirectionalLightComponent::setAttribute(std::string name, float value) {
	// if (name == "ambient") {
	// 	this->ambient = value;
	// } else if (name == "diffuseColor.r") {
	// 	this->color.x = value;
	// } else if (name == "diffuseColor.g") {
	// 	this->color.y = value;
	// } else if (name == "diffuseColor.b") {
	// 	this->color.z = value;
	// } else if (name == "direction.x") {
	// 	this->direction.x = value;
	// } else if (name == "direction.y") {
	// 	this->direction.y = value;
	// } else if (name == "direction.z") {
	// 	this->direction.z = value;
	// } 
}

void FADirectionalLightComponent::bind() {
	// glUniform1f(ambientLocation, *ambient);
	glUniform4fv(colorLocation, 1, &(*color)[0]);
	glm::mat4 m = *this->modelMatrix;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	
	glm::vec4 v = m * glm::vec4(0,0,1,1);
	glm::vec3 d = glm::vec3(v.x, v.y, v.z);
	glUniform3fv(directionLocation, 1, &d[0]);
}

void FADirectionalLightComponent::setUpLocations(GLint shaderProgram) {
	// ambientLocation = glGetUniformLocation(shaderProgram, "ambient");
	colorLocation = glGetUniformLocation(shaderProgram, "diffuseColor");
	directionLocation = glGetUniformLocation(shaderProgram, "direction");

	// if (ambientLocation == -1)
	// 	std::cout << "Error getting ambientLocation in " << name << " component!" << std::endl;
	if (colorLocation == -1)
		std::cout << "Error getting colorLocation in " << name << " component!" << std::endl;
	if (directionLocation == -1)
		std::cout << "Error getting directionLocation in " << name << " component!" << std::endl;

}

void FADirectionalLightComponent::setColor(glm::vec4 *color) {
	this->color = color;
}

void FADirectionalLightComponent::setModelMatrix(glm::mat4 *modelMatrix) {
	this->modelMatrix = modelMatrix;
}

// void FADirectionalLightComponent::setAmbientComponent(float *ambientComponent) {
// 	this->ambient = ambientComponent;
// }

void FADirectionalLightComponent::setShadow(bool shadow) {
	this->hasShadow = shadow;
	if (hasShadow) {
		lightOutput = "";
	} else {
		lightOutput = "light1";
	}
}

// Diffuse light material

FADiffuseLightComponent::FADiffuseLightComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform vec4 diffuseColor1;\nuniform vec3 lightPosition;\nuniform float radius;\n";
	fragmentMain = "vec3 lightDir = normalize(lightPosition-pass_Position.xyz);\n"
	"vec4 light2 = max(dot(lightDir,pass_Normal.xyz), 0.0) * diffuseColor1;\n"
	//falloff
	"float falloff = length(lightPosition-pass_Position.xyz)/radius + 1;\n"
	"falloff = 1/(falloff*falloff);\n"
	"light2 = falloff * light2;\n";
	// fragmentOutput = "(OTHER_OUT)";
	lightOutput = "light2";
	name = "Diffuse light";
	requirements.push_back(new FAVertexNormalComponent);
	requirements.push_back(new FAVertexPositionComponent);
	modelData = false;
}

void FADiffuseLightComponent::setAttribute(std::string name, float value) {

}

void FADiffuseLightComponent::bind() {
	glUniform4fv(colorLocation, 1, &(*color)[0]);
	glUniform3fv(positionLocation, 1, &(*position)[0]);
	glUniform1fv(radiusLocation, 1, &(*radius));
}

void FADiffuseLightComponent::setUpLocations(GLint shaderProgram) {
	colorLocation = glGetUniformLocation(shaderProgram, "diffuseColor1");
	positionLocation = glGetUniformLocation(shaderProgram, "lightPosition");
	radiusLocation = glGetUniformLocation(shaderProgram, "radius");
	
	// if (ambientLocation == -1)
	// 	std::cout << "Error getting ambientLocation in " << name << " component!" << std::endl;
	if (colorLocation == -1)
		std::cout << "Error getting colorLocation in " << name << " component!" << std::endl;
	if (positionLocation == -1)
		std::cout << "Error getting positionLocation in " << name << " component!" << std::endl;
	if (radiusLocation == -1)
		std::cout << "Error getting radiusLocation in " << name << " component!" << std::endl;
}

void FADiffuseLightComponent::setColor(glm::vec4 *color) {
	this->color = color;
}

void FADiffuseLightComponent::setPosition(glm::vec3 *position) {
	this->position = position;
}

void FADiffuseLightComponent::setRadius(float *radius) {
	this->radius = radius;
}

//Ambient light material

FAAmbientLightComponent::FAAmbientLightComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform vec4 ambientColor;\n";
	fragmentMain = "";
	lightOutput = "ambientColor";
	name = "Ambient light";
	modelData = false;
}

void FAAmbientLightComponent::setAttribute(std::string name, float value) {

}

void FAAmbientLightComponent::bind() {
	glUniform4fv(colorLocation, 1, &(*color)[0]);
}

void FAAmbientLightComponent::setUpLocations(GLint shaderProgram) {
	colorLocation = glGetUniformLocation(shaderProgram, "ambientColor");

	if (colorLocation == -1)
		std::cout << "Error getting colorLocation in " << name << " component!" << std::endl;

}

void FAAmbientLightComponent::setColor(glm::vec4 *color) {
	this->color = color;
}

//Color material

FAColorComponent::FAColorComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform vec4 color;\n";
	fragmentMain = "";
	// fragmentOutput = "(OTHER_OUT) * color";
	materialOutput = " * color";
	name = "color";
	modelData = false;
}

void FAColorComponent::setAttribute(std::string name, float value) {

}

void FAColorComponent::bind() {
	glUniform4fv(this->colorUniformLocation, 1, &color[0]);
}

void FAColorComponent::setUpLocations(GLint shaderProgram) {
	this->colorUniformLocation = glGetUniformLocation(shaderProgram, "color");
	if (colorUniformLocation == -1)
		std::cout << "Error getting colorUniformLocation in " << name << " component!" << std::endl;
}

void FAColorComponent::setColor(glm::vec4 &color) {
	this->color = color;
}

//texture material

FATextureComponent::FATextureComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform sampler2D mytextureSampler;\n";
	fragmentMain = "vec4 textureColor = texture(mytextureSampler, pass_UV);";
	// fragmentOutput = "(OTHER_OUT) * textureColor";
	materialOutput = " * textureColor";
	name = "texture";
	requirements.push_back(new FAVertexUVComponent);
	modelData = false;
}

void FATextureComponent::setAttribute(std::string name, float value) {

}

void FATextureComponent::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *this->texture);
	// std::cout << *this->texture << std::endl;
	glUniform1i(textureUniformLocation, 0);
}

void FATextureComponent::setUpLocations(GLint shaderProgram) {
	this->textureUniformLocation = glGetUniformLocation(shaderProgram, "mytextureSampler");
	if (textureUniformLocation == -1)
		std::cout << "Error getting textureUniformLocation in " << name << " component!" << std::endl;
}

void FATextureComponent::setTexture(GLuint texture) {
	this->texture = &texture;
}

void FATextureComponent::setTexture(GLuint *texture) {
	this->texture = texture;
}

//textureArray material

FATextureArrayComponent::FATextureArrayComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform sampler2DArray mytextureSampler;\n";
	fragmentMain = "vec4 textureColor = vec4(1,1,1,1); textureColor.x = texture(mytextureSampler, vec3(pass_UV, 0)).r;textureColor.y = texture(mytextureSampler, vec3(pass_UV, 1)).r;textureColor.z = texture(mytextureSampler, vec3(pass_UV, 2)).r;";
	// fragmentOutput = "(OTHER_OUT) * textureColor";
	materialOutput = " * textureColor";
	name = "texture";
	requirements.push_back(new FAVertexUVComponent);
	modelData = false;
}

void FATextureArrayComponent::setAttribute(std::string name, float value) {

}

void FATextureArrayComponent::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, *this->texture);
	glUniform1i(textureUniformLocation, 0);
}

void FATextureArrayComponent::setUpLocations(GLint shaderProgram) {
	this->textureUniformLocation = glGetUniformLocation(shaderProgram, "mytextureSampler");
	if (textureUniformLocation == -1)
		std::cout << "Error getting textureUniformLocation in " << name << " component!" << std::endl;
}

void FATextureArrayComponent::setTexture(GLuint texture) {
	this->texture = &texture;
}

void FATextureArrayComponent::setTexture(GLuint *texture) {
	this->texture = texture;
}

void FATextureArrayComponent::setLayer(int layer) {
	this->layer = layer;
}

//CSM material

FACSMComponent::FACSMComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform sampler2DArray shadowMap;\nuniform mat4 inverseShadowMatrix[4];";
	fragmentMain = "int index = 0; "
		"if (gl_FragCoord.z/gl_FragCoord.w < 4) {\n"
	    "index = 0;\n"
	    "} else if (gl_FragCoord.z/gl_FragCoord.w < 12) {\n"
	    "    index = 1;\n"
	    "} else if (gl_FragCoord.z/gl_FragCoord.w < 30) {\n"
	    "    index = 2;\n"
	    "} else if (gl_FragCoord.z/gl_FragCoord.w < 100) {\n"
	    "    index = 3;\n"
	    "} else {\n"
	    "    index = -1;\n"
	    "}\n"
	    "float shadow = 1.0;\n"
	    "vec4 shadowCoordinateWdivide;"
	    "float dist;"
	    "if (index != -1) {\n"
	    "	if (pass_Position.w > 0.0) {\n"
	    "	shadowCoordinateWdivide = (inverseShadowMatrix[index] * pass_Position) / pass_Position.w;\n"
	    "    	dist = texture(shadowMap,vec3(shadowCoordinateWdivide.st, index)).r;\n"
	    "       if (dist > 0) {\n"
	    // "		shadow = dist;"
	    "       	if (dist < shadowCoordinateWdivide.z - 0.002)\n"
	    "           	shadow =  0.0;\n"
	    "        }\n"
	    "	}\n"
	    "}";
	// fragmentOutput = "(OTHER_OUT) + shadow * lambertian";
	    lightOutput = "(light1 * shadow)";
	name = "CSM";
	requirements.push_back(new FAVertexPositionComponent);
	modelData = false;
}

void FACSMComponent::setAttribute(std::string name, float value) {

}

void FACSMComponent::bind() {
	// std::cout << *frustums << std::endl;
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D_ARRAY, *this->texture);
	glUniform1i(textureUniformLocation, 3);
	glUniformMatrix4fv(inverseShadowMatrixUniformLocation, (GLsizei) 4, GL_FALSE, &inverseShadowMatrix[0][0][0]);
	// std::cout << *frustums << std::endl;
	// std::cout << inverseShadowMatrix[0][0][0] << ", " << inverseShadowMatrix[0][0][1] << ", " << inverseShadowMatrix[0][0][2] << ", " << inverseShadowMatrix[0][0][3] << std::endl;
	// std::cout << inverseShadowMatrix[0][1][0] << ", " << inverseShadowMatrix[0][1][1] << ", " << inverseShadowMatrix[0][1][2] << ", " << inverseShadowMatrix[0][1][3] << std::endl;
	// std::cout << inverseShadowMatrix[0][2][0] << ", " << inverseShadowMatrix[0][2][1] << ", " << inverseShadowMatrix[0][2][2] << ", " << inverseShadowMatrix[0][2][3] << std::endl;
	// std::cout << inverseShadowMatrix[0][3][0] << ", " << inverseShadowMatrix[0][3][1] << ", " << inverseShadowMatrix[0][3][2] << ", " << inverseShadowMatrix[0][3][3] << std::endl;
}

void FACSMComponent::setUpLocations(GLint shaderProgram) {
	this->textureUniformLocation = glGetUniformLocation(shaderProgram, "shadowMap");
	if (textureUniformLocation == -1)
		std::cout << "Error getting textureUniformLocation in " << name << " component!" << std::endl;
	this->inverseShadowMatrixUniformLocation = glGetUniformLocation(shaderProgram, "inverseShadowMatrix");
	if (inverseShadowMatrixUniformLocation == -1)
		std::cout << "Error getting inverseShadowMatrixUniformLocation in " << name << " component!" << std::endl;

}

void FACSMComponent::setTexture(GLuint *texture) {
	this->texture = texture;
}

void FACSMComponent::setFrustums(int *frustums) {
	this->frustums = frustums;
	fragmentIO = "uniform sampler2DArray shadowMap;\nuniform mat4 inverseShadowMatrix[" + std::to_string(*frustums) + "];";
}

void FACSMComponent::setInverseShadowMatrix(glm::mat4 *inverseShadowMatrix) {
	this->inverseShadowMatrix = inverseShadowMatrix;
	// std::cout << "setting inverse matrix!" << std::endl;
}

// Skeletal animation

FASkinningVertexComponent::FASkinningVertexComponent() {

	//TODO dynamic allocation of bone matrices
	
	vertexIO = "layout(location = 4) in vec4 in_Index;\nlayout(location = 5) in vec4 in_Weight;\nuniform mat4 bones[3];";
	vertexMain = "";
	fragmentIO = "";
	fragmentMain = "";
	lightOutput = "";
	name = "SkinningVertex";
	// requirements.push_back(new FAVertexPositionComponent);
	modelData = true;
}

void FASkinningVertexComponent::setAttribute(std::string name, float value) {

}

void FASkinningVertexComponent::bind() {
	glUniformMatrix4fv(bonesLocation, bonesSize, GL_FALSE, bones);
}

void FASkinningVertexComponent::setUpLocations(GLint shaderProgram) {
	this->bonesLocation = glGetUniformLocation(shaderProgram, "bones");
	if (bonesLocation == -1)
		std::cout << "Error getting bonesLocation in " << name << " component!" << std::endl;
}

void FASkinningVertexComponent::setBonesArray(GLsizei size, const GLfloat *value) {
	this->bonesSize = size;
	this->bones = value;
}

FASkinningComponent::FASkinningComponent() {

	vertexIO = "";
	vertexMain = "int index = int(in_Index.x);"
	"vec4 skintransform = (bones[index] * in_Weight.x) * vec4(in_Position.xyz, 1.0);"
	"index = int(in_Index.y);"
	"skintransform = skintransform + (bones[index] * in_Weight.y) * vec4(in_Position.xyz, 1.0);"
	"index = int(in_Index.z);"
	"skintransform = skintransform + (bones[index] * in_Weight.z) * vec4(in_Position.xyz, 1.0);"
	"index = int(in_Index.w);"
	"skintransform = skintransform + (bones[index] * in_Weight.w) * vec4(in_Position.xyz, 1.0);"
	"gl_Position = MVPMatrix * skintransform;";
	fragmentIO = "";
	fragmentMain = "";
	lightOutput = "";
	name = "Skinning";
	requirements.push_back(new FASkinningVertexComponent);
	modelData = false;
}

void FASkinningComponent::setAttribute(std::string name, float value) {

}

void FASkinningComponent::bind() {
	
}

void FASkinningComponent::setUpLocations(GLint shaderProgram) {
	
}

FAOpacityComponent::FAOpacityComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "";
	fragmentMain = "";
	// fragmentOutput = "(OTHER_OUT) * textureColor";
	materialOutput = " * ";
	name = "texture";
	requirements.push_back(new FAVertexUVComponent);
	modelData = false;

}
void FAOpacityComponent::setAttribute(std::string name, float value) {
	
}
void FAOpacityComponent::bind() {
	
}
void FAOpacityComponent::setUpLocations(GLint shaderProgram) {
	
}







