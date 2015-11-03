#include <FA/FAGUITexturedPlane.h>

FAGUITexturedPlane::FAGUITexturedPlane() {
	this->position = glm::vec2(0.25,0.25);
	this->size = glm::vec2(0.5,0.5);
	this->mesh = new FAMesh("square");
	this->shader = new FAShader("FATexture");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->textureLocation = glGetUniformLocation(this->shader->shaderProgram, "text");
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");
	if (this->textureLocation == -1)
		std::cout << "Cannot find texture location" << std::endl;
	if (this->positionLocation == -1)
		std::cout << "Cannot find position location" << std::endl;
	if (this->sizeLocation == -1)
		std::cout << "Cannot find size location" << std::endl;
	glUseProgram(0);
}

FAGUITexturedPlane::FAGUITexturedPlane(GLuint texture) : FAGUITexturedPlane() {
	this->texture = texture;
}

void FAGUITexturedPlane::update(float dt) {

}

void FAGUITexturedPlane::render() {
	glm::vec2 pos = glm::vec2((this->globalTransformation.x*2-1),this->globalTransformation.y*2-1);
	glm::vec2 size = glm::vec2(this->size.x*2,this->size.y*2);
    glUseProgram(shader->shaderProgram);
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureLocation, 0);
	glUniform2fv(positionLocation, 1, &pos[0]);
	glUniform2fv(sizeLocation, 1, &size[0]);

    this->mesh->render();
}

FAGUITexturedPlane::~FAGUITexturedPlane() {

}