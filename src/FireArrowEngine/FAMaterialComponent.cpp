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




