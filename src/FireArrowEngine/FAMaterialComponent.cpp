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
	if (name == "ambient") {
		this->ambient = value;
	} else if (name == "diffuseColor.r") {
		this->color.x = value;
	} else if (name == "diffuseColor.g") {
		this->color.y = value;
	} else if (name == "diffuseColor.b") {
		this->color.z = value;
	} else if (name == "direction.x") {
		this->direction.x = value;
	} else if (name == "direction.y") {
		this->direction.y = value;
	} else if (name == "direction.z") {
		this->direction.z = value;
	} 
}

void FADirectionalLightComponent::bind() {
	glUniform1f(ambientLocation, ambient);
	glUniform4fv(colorLocation, 1, &color[0]);
	glUniform3fv(directionLocation, 1, &direction[0]);
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

void FADirectionalLightComponent::setColor(glm::vec4 &color) {
	this->color = color;
}

void FADirectionalLightComponent::setDirection(glm::vec3 direction) {
	this->direction = direction;
}

void FADirectionalLightComponent::setAmbientComponent(float ambientComponent) {
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
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glUniform1i(textureUniformLocation, 0);
}

void FATextureComponent::setUpLocations(GLint shaderProgram) {
	this->textureUniformLocation = glGetUniformLocation(shaderProgram, "mytextureSampler");
	if (textureUniformLocation == -1)
		std::cout << "Error getting textureUniformLocation in " << name << " component!" << std::endl;
}

void FATextureComponent::setTexture(GLuint texture) {
	this->texture = texture;
}





