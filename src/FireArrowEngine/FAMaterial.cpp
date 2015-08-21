#include <FA/FAMaterial.h>

FAMaterial::FAMaterial() {

	// components.push_back(new FADirectionalLightComponent);

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

FAMaterialComponent* FAMaterial::getComponentByName(std::string name) {
	for (int i = 0; i < components.size(); ++i) {
		if (name == components[i]->getName()) {
			return components[i];
		}
	}
	return nullptr;
}

void FAMaterial::buildShader() {

	isBuilt = true;

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

	// std::cout << fragmentShader << std::endl;

	fragmentShader += "Frag_Data = ";
	fragmentShader += output;
	fragmentShader += ";\nFrag_Data.w = 1.0;\n}\n";

	this->shader = new FAShader(&vertexShader, &fragmentShader);

	for (FAMaterialComponent *c : components)
		c->setUpLocations(this->shader->shaderProgram);

}

void FAMaterial::setColor(glm::vec4 &color) {
	if (!this->hasColor) {
		this->hasColor = true;
		components.push_back(new FAColorComponent);
		isBuilt = false;
	}

	FAColorComponent *comp = (FAColorComponent *)getComponentByName("color");
	if (comp != nullptr) {
		comp->setColor(color);
	}
}

void FAMaterial::setDirectionalLight(glm::vec3 &direction, glm::vec4 &color, float ambientComponent) {
	FADirectionalLightComponent *component = new FADirectionalLightComponent;
	component->setDirection(direction);
	component->setColor(color);
	component->setAmbientComponent(ambientComponent);
	components.push_back(component);
	isBuilt = false;
}

void FAMaterial::setTexture(GLuint texture) {
	FATextureComponent *textureComponent = new FATextureComponent();
	textureComponent->setTexture(texture);
	addMaterialComponent(textureComponent);
}

void FAMaterial::hasVertexColor(bool value) {
	if (value) {
		components.push_back(new FAVertexColorComponent);
		isBuilt = false;
	}
}

void FAMaterial::hasVertexNormal(bool value) {
	if (value) {
		components.push_back(new FAVertexNormalComponent);
		isBuilt = false;
	}
}

void FAMaterial::hasVertexUV(bool value) {
	if (value) {
		components.push_back(new FAVertexUVComponent);
		isBuilt = false;
		std::cout << "model has UV!" << std::endl;
	}
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

void FAMaterial::create() {
	isCreated = true;
	for (FAMaterialComponent *component : pendingComponents) {
		addMaterialComponent(component);
	}
	buildShader();
}

bool FAMaterial::addMaterialComponent(FAMaterialComponent *component) {
	if (isCreated) {
		if (getComponentByName(component->getName()) == nullptr) {
			if (component->requiresModelData()) {
				std::cout << "The model is missing " << component->getName() << " data!" << std::endl;
				return false;
			}
			for (FAMaterialComponent *requiredComponent : *component->getRequirements()) {
				if (!addMaterialComponent(requiredComponent)) {
					return false;
				}
			}
			components.push_back(component);
			std::cout << "added component " << component->getName() << std::endl;
			isBuilt = false;
			return true;
		}
		return true;
	} else {
		this->pendingComponents.push_back(component);
		return true;
	}
}

void FAMaterial::bind() {
	if (!isBuilt) {
		buildShader();
	}

	glm::mat4 MVPMatrix = viewProjectionMatrix * modelMatrix;
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