//
//  WireMaterial.cpp
//  FA
//
//  Created by Simon Nilsson on 4/1/16.
//  Copyright © 2016 Axenu. All rights reserved.
//

#include "WireMaterial.h"

WireMaterial::WireMaterial() {
	this->shader = new FAShader("Basic");
	
	MVPLocation = glGetUniformLocation(this->shader->shaderProgram, "MVPMatrix");
	colorLocation = glGetUniformLocation(this->shader->shaderProgram, "ucolor");
	
	if (MVPLocation == -1) { std::cout << "MVPLocation failed!" << std::endl; }
	if (colorLocation == -1) { std::cout << "colorLocation failed!" << std::endl; }
	this->color = glm::vec4(1,1,1,1);
}

WireMaterial::~WireMaterial() {
	
}

void WireMaterial::bind() {
	glm::mat4 m = this->viewProjectionMatrix * this->modelMatrix;
	glUseProgram(shader->shaderProgram);
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &m[0][0]);
	glUniform4fv(colorLocation, 1, &color[0]);
}

void WireMaterial::setViewProjectionwMatrix(glm::mat4 &VPMatrix) {
	this->viewProjectionMatrix = VPMatrix;
}

void WireMaterial::setModelMatrix(glm::mat4 &modelMatrix) {
	this->modelMatrix = modelMatrix;
}

void WireMaterial::setColor(glm::vec4 color) {
	this->color = color;
}