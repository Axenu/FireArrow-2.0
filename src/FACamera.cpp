#include "FACamera.h"

FACamera::FACamera() {

}

FACamera::FACamera(float fov, float aspect, float near, float far) {
    this->fieldOfView = fov;
    this->aspectRatio = aspect;
    this->nearPlane = near;
    this->farPlane = far;
    this->perspective = true;
    this->position = glm::vec3(0,1,1);
    // this->rotation.x = 1.0;
    initProjection();
}

FACamera::FACamera(float fov, int _width, int _height, float near, float far) {
    this->perspective = true;
    this->width = _width;
    this->height = _height;
    this->nearPlane = near;
    this->farPlane = far;
    this->fieldOfView = fov;
    this->aspectRatio = width/height;
    this->position = glm::vec3(0,0,3);
    // this->rotation.x = 1.0;
    initProjection();
}

void FACamera::useView() {
    viewMatrix = glm::rotate(glm::mat4(), rotation.x, glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, rotation.y, glm::vec3(0, 1, 0));
    viewMatrix = glm::rotate(viewMatrix, rotation.z, glm::vec3(0, 0, 1));
    viewMatrix = glm::translate(viewMatrix, -position);
    VPMatrix = projectionMatrix * viewMatrix;
}

void FACamera::initProjection() {
	projectionMatrix = glm::perspectiveFov(degreesToRadians(fieldOfView), width, height, nearPlane, farPlane);
}
	
FACamera::~FACamera() {

}

float FACamera::degreesToRadians(float degrees) {
    return degrees * (M_PI / 180.0);
}