#include "FAModel.h"

FAModel::FAModel() {

}

FAModel::FAModel(FAMesh &mesh) {
	this->mesh = mesh;
}

FAModel::FAModel(FAMesh &mesh, FAMaterial &material) {
	this->mesh = mesh;
	this->material = material;
}

void FAModel::setMaterial(FAMaterial &material) {
	this->material = material;
}

void FAModel::setMesh(FAMesh &mesh) {
	this->mesh = mesh;
}

void FAModel::setMesh(std::string path) {
	this->mesh = FAMesh(path);
}

FAMaterial &FAModel::getMaterial() {
	return this->material;
}

const FAMesh &FAModel::getMesh() const {
	return this->mesh;
}

void FAModel::render(FACamera *camera) {
	// material.setViewProjectionwMatrix(&camera->VPMatrix);
	material.bind();
	mesh.render();
}

void FAModel::update(float dt) {

}

FAModel::~FAModel() {

}