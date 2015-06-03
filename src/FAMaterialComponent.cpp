#include "FAMaterialComponent.h"

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
