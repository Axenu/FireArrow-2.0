#include <FA/FAGUIPlane.h>

FAGUIPlane::FAGUIPlane() {
	this->position = glm::vec2(0,0);
	this->size = glm::vec2(0.5,0.5);
	this->color = glm::vec4(1,0,0,0.5);
	this->mesh = new FAMesh("square");
	this->shader = new FAShader("FAPlane");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->colorLocation = glGetUniformLocation(this->shader->shaderProgram, "color");
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");
	if (this->positionLocation == -1)
		std::cout << "Cannot find position location" << std::endl;
	if (this->sizeLocation == -1)
		std::cout << "Cannot find size location" << std::endl;
	glUseProgram(0);
}

void FAGUIPlane::onUpdate(float dt) {

}

void FAGUIPlane::onRender() {
	glm::vec2 pos = glm::vec2((this->globalTransformation.x*2-1),this->globalTransformation.y*2-1);
	glm::vec2 size = glm::vec2(this->size.x*2,this->size.y*2);
    glUseProgram(shader->shaderProgram);
	glUniform2fv(positionLocation, 1, &pos[0]);
	glUniform2fv(sizeLocation, 1, &size[0]);
	glUniform4fv(colorLocation, 1, &color[0]);

    this->mesh->render();
}

FAGUIPlane::~FAGUIPlane() {

}