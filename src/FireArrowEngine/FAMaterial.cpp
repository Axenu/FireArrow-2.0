#include <FA/FAMaterial.h>

FAMaterial::FAMaterial() {

	// FAColorComponent *c = new FAColorComponent();

	components.push_back(new FAVertexNormalComponent);
	components.push_back(new FAVertexColorComponent);
	components.push_back(new FADirectionalLightComponent);

	this->vertexIO = "#version 400 core \n uniform mat4 MVPMatrix;"
		"layout(location = 0) in vec3 in_Position;\n";
	this->vertexMain = "gl_Position = MVPMatrix * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);\n";

	this->fragmentIO = "#version 400 core \nout vec4 Frag_Data;\n";
	this->fragmentMain = "";
	this->fragmentOutput = "Frag_Data = pass_Color;\n";

	// this->modelMatrix = glm::mat4();
	// this->shader = new FAShader("Basic");
	buildShader();
	glUseProgram(this->shader->shaderProgram);
	MVPLocation = glGetUniformLocation(this->shader->shaderProgram, "MVPMatrix");
	if (MVPLocation == -1) {
		std::cout << "MVPLocation failed!" << std::endl;
	}
	glUseProgram(0);
}

void FAMaterial::buildShader() {

	std::string vertexShader = "", fragmentShader = "";

	vertexShader += this->vertexIO;
	for (FAMaterialComponent *c : components)
		vertexShader += c->getVertexIO(); 
	vertexShader += "void main() {\n";
	vertexShader += this->vertexMain;
	for (FAMaterialComponent *c : components)
		vertexShader += c->getVertexMain(); 
	vertexShader += "}\n";

	fragmentShader += this->fragmentIO;
	for (FAMaterialComponent *c : components)
		fragmentShader += c->getFragmentIO(); 
	fragmentShader += "void main() {\n";
	fragmentShader += this->fragmentMain;
	for (FAMaterialComponent *c : components)
		fragmentShader += c->getFragmentMain();

	std::string output = "vec4(1,1,1,1)";
	for (FAMaterialComponent *c : components) {
		std::string cOut = c->getFragmentMainOutput();
		size_t start_pos = cOut.find("OTHER_OUT");
		if(start_pos != std::string::npos)
			cOut.replace(start_pos, 9, output);
  		// std::replace( cOut.begin(), cOut.end(), "OTHER_OUT", output);
  		output = cOut;
	}

	std::cout << fragmentShader << std::endl;

	fragmentShader += "Frag_Data = ";
	fragmentShader += output;
	fragmentShader += ";\nFrag_Data.w = 1.0;\n}\n";

	this->shader = new FAShader(&vertexShader, &fragmentShader);

	for (FAMaterialComponent *c : components)
		c->setUpLocations(this->shader->shaderProgram);

}

void FAMaterial::setAttribute(std::string name, float value) {
	std::size_t place = name.find(".");
	std::string compName = name.substr(0,place);
	for (FAMaterialComponent *c : components) {
		if (c->getName() == compName) {
			c->setAttribute(name.substr(place), value);
			break;
		}
	}
	//check all possible commands //supposedly prefix only
	//if found send to the component with suffix
}

void FAMaterial::bind() {
	// for (FAMaterialComponent *c : components) {
	// 	c->render();
	// }
	//setup ALL attributes, depth test, uniforms etc.

	glm::mat4 MVPMatrix = viewProjectionMatrix * modelMatrix;
	// glm::mat4 MVPMatrix = glm::mat4();
	// std::cout << "glm::mat4: " << std::endl;
	// std::cout << MVPMatrix[0][0] << ", " << MVPMatrix[0][1] << ", " << MVPMatrix[0][2] << ", " << MVPMatrix[0][3] << std::endl;
	// std::cout << MVPMatrix[1][0] << ", " << MVPMatrix[1][1] << ", " << MVPMatrix[1][2] << ", " << MVPMatrix[1][3] << std::endl;
	// std::cout << MVPMatrix[2][0] << ", " << MVPMatrix[2][1] << ", " << MVPMatrix[2][2] << ", " << MVPMatrix[2][3] << std::endl;
	// std::cout << MVPMatrix[3][0] << ", " << MVPMatrix[3][1] << ", " << MVPMatrix[3][2] << ", " << MVPMatrix[3][3] << std::endl;
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &MVPMatrix[0][0]);
	for (FAMaterialComponent *c : components)
		c->bind();

}

void FAMaterial::setViewProjectionwMatrix(glm::mat4 *VPMatrix) {
	this->viewProjectionMatrix = *VPMatrix;
}

void FAMaterial::setModelMatrix(glm::mat4 &modelMatrix) {
	this->modelMatrix = modelMatrix;
}

FAMaterial::~FAMaterial() {
	
}