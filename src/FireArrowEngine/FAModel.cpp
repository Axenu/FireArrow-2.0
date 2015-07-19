#include <FA/FAModel.h>

FAModel::FAModel() {

}

FAModel::FAModel(FAMesh &mesh) {
	this->mesh = mesh;
}

FAModel::FAModel(FAMesh &mesh, FAMaterial &material) {
	this->mesh = mesh;
	this->material = material;
	this->material.hasVertexNormal(this->mesh.hasVertexNormal());
	this->material.hasVertexColor(this->mesh.hasVertexColor());
}

void FAModel::setMaterial(FAMaterial &material) {
	this->material = material;
	this->material.hasVertexNormal(this->mesh.hasVertexNormal());
	this->material.hasVertexColor(this->mesh.hasVertexColor());
}

void FAModel::setMesh(FAMesh &mesh) {
	this->mesh = mesh;
	this->material.hasVertexNormal(this->mesh.hasVertexNormal());
	this->material.hasVertexColor(this->mesh.hasVertexColor());
}

void FAModel::setMesh(std::string path) {
	this->mesh = FAMesh(path);
	this->material.hasVertexNormal(this->mesh.hasVertexNormal());
	this->material.hasVertexColor(this->mesh.hasVertexColor());
}

FAMaterial &FAModel::getMaterial() {
	return this->material;
}

const FAMesh &FAModel::getMesh() const {
	return this->mesh;
}

void FAModel::onUpdate(float dt) {
	this->material.setModelMatrix(this->modelMatrix);
}

FAModel::~FAModel() {

}