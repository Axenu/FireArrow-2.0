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
	fragmentOutput = "OTHER_OUT";
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
	vertexMain = "pass_Normal = vec4(in_Normal, 1.0);\n";
	fragmentIO = "in vec4 pass_Normal;\n";
	fragmentMain = "";
	fragmentOutput = "OTHER_OUT";
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
	fragmentOutput = "(OTHER_OUT) * pass_Color";
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
	fragmentOutput = "OTHER_OUT";
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
	fragmentIO = "uniform float ambient;\nuniform vec4 diffuseColor;\nuniform vec3 direction;\n";
	fragmentMain = "vec3 normal = normalize(pass_Normal.xyz);\n"
    "vec3 lightDir = normalize(direction);\n"
    "float lambertian = max(dot(lightDir,normal), 0.0);\n";
	fragmentOutput = "(OTHER_OUT) * (ambient * vec4(1,1,1,1) + lambertian * diffuseColor)";
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
	glUniform1f(ambientLocation, *ambient);
	glUniform4fv(colorLocation, 1, &(*color)[0]);
	glUniform3fv(directionLocation, 1, &(*direction)[0]);
}

void FADirectionalLightComponent::setUpLocations(GLint shaderProgram) {
	ambientLocation = glGetUniformLocation(shaderProgram, "ambient");
	colorLocation = glGetUniformLocation(shaderProgram, "diffuseColor");
	directionLocation = glGetUniformLocation(shaderProgram, "direction");

	if (ambientLocation == -1)
		std::cout << "Error getting ambientLocation in " << name << " component!" << std::endl;
	if (colorLocation == -1)
		std::cout << "Error getting colorLocation in " << name << " component!" << std::endl;
	if (directionLocation == -1)
		std::cout << "Error getting directionLocation in " << name << " component!" << std::endl;

}

void FADirectionalLightComponent::setColor(glm::vec4 *color) {
	this->color = color;
}

void FADirectionalLightComponent::setDirection(glm::vec3 *direction) {
	this->direction = direction;
}

void FADirectionalLightComponent::setAmbientComponent(float *ambientComponent) {
	this->ambient = ambientComponent;
}

//Color material

FAColorComponent::FAColorComponent() {
	vertexIO = "";
	vertexMain = "";
	fragmentIO = "uniform vec4 color;\n";
	fragmentMain = "";
	fragmentOutput = "(OTHER_OUT) * color";
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
	fragmentOutput = "(OTHER_OUT) * textureColor";
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
	fragmentOutput = "(OTHER_OUT) * textureColor";
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
	    "	vec4 shadowCoordinateWdivide = (inverseShadowMatrix[index] * pass_Position) / pass_Position.w;\n"
	    "	if (pass_Position.w > 0.0) {\n"
	    "    	dist = texture(shadowMap,vec3(shadowCoordinateWdivide.st, index)).r;\n"
	    // "       if (dist > 0) {\n"
	    "		shadow = dist;"
	    // "       	if (dist - 0.00001 < shadowCoordinateWdivide.z)\n"
	    // "           	shadow =  0.5;\n"
	    // "        }\n"
	    "	}\n"
	    "}";
	fragmentOutput = "(OTHER_OUT) * dist";
	name = "CSM";
	requirements.push_back(new FAVertexPositionComponent);
	modelData = false;
}

void FACSMComponent::setAttribute(std::string name, float value) {

}

void FACSMComponent::bind() {
	// std::cout << *frustums << std::endl;
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D_ARRAY, *this->texture);
	glUniform1i(textureUniformLocation, 1);
	glUniformMatrix4fv(inverseShadowMatrixUniformLocation, (GLsizei) 4, GL_FALSE, inverseShadowMatrix);
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
	std::cout << "setting inverse matrix!" << std::endl;
}





