#include <FA/FAGUILabel.h>

FAGUILabel::FAGUILabel() {
	mesh = new FAMesh("square");
	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);
	this->verticesSize = 0;
	this->indicesSize = 0;

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
//	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);
}

FAGUILabel::FAGUILabel(FAFont *font) {
	mesh = new FAMesh("square");

	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);
	this->verticesSize = 0;
	this->indicesSize = 0;
	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
//	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);

	this->font = font;
	this->setHeight(font->getHeight());
}

void FAGUILabel::setText(std::string text) {
	this->text = text;
	//load text from font
	
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	
	float x = 0.0f;
	glyph g = font->glyphs[(int)text[0]];
	
	//custom anchorpoint?
	
	for (int i = 0; i < text.length(); i++) {
		//v0 |_
		vertices.push_back(x + g.x1); //x1
		vertices.push_back(g.y1); //y1
		
		vertices.push_back(g.u1); //u1
		vertices.push_back(g.v1); //v1
		
		//v1 |-
		vertices.push_back(x + g.x1); //x1
		vertices.push_back(g.y2); //y2
		
		vertices.push_back(g.u1); //u
		vertices.push_back(g.v2); //v2
		//v2-|
		vertices.push_back(x + g.x2); //x2
		vertices.push_back(g.y2); //y2
		
		vertices.push_back(g.u2); //u
		vertices.push_back(g.v2); //v
		
		//v3 _|
		vertices.push_back(x + g.x2); //x2
		vertices.push_back(g.y1); //y1
		
		vertices.push_back(g.u2); //u2
		vertices.push_back(g.v1); //v
		
		//indices
		indices.push_back(i*4+0);
		indices.push_back(i*4+2);
		indices.push_back(i*4+1);
		indices.push_back(i*4+0);
		indices.push_back(i*4+3);
		indices.push_back(i*4+2);
		
		x += g.xAdvance;
		g = font->glyphs[(int)text[i+1]];
	}

	if (verticesSize < vertices.size()) {
		glDeleteBuffers(1, &VBO);
		glGenBuffers(1, &VBO);
		this->verticesSize = vertices.size();
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	if (indicesSize < indices.size()) {
		glDeleteBuffers(1, &EBO);
		glGenBuffers(1, &EBO);
		this->indicesSize = indices.size();
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glDeleteVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
//	int attributes = 4;
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) (2 * sizeof(GLfloat)));
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

float FAGUILabel::getWidth() {
	glyph g = font->glyphs[(int)text[0]];
	float width = g.xAdvance;
	for (int i = 1; i < text.length(); i++) {
		g = font->glyphs[(int)text[i]];
		width += g.xAdvance;
	}
	
	return width;
}

std::string FAGUILabel::getText() {
	return this->text;
}

void FAGUILabel::onUpdate(float dt) {

}

//void FAGUILabel::renderCharacter(int character, float x, float y, float charWidth, float charHeigth) {
//    
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, font->texture[character]);
//    
//    glUseProgram(shader->shaderProgram);
//
//    glUniform3f(positionLocation, x + this->globalTransformation.x*2-1, -y + this->globalTransformation.y*2-1, 0);
//    glUniform2f(sizeLocation, charWidth, charHeigth);
//
//    this->mesh->render();
//	
//}

void FAGUILabel::onRender() {
	
	glUseProgram(shader->shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font->fontTexture);
		
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	glUniform2f(positionLocation, this->globalTransformation.x, 1-this->globalTransformation.y);
	
	glDrawElements(GL_TRIANGLES, 6 * (int)text.length(), GL_UNSIGNED_INT, NULL);
	
}

FAGUILabel::~FAGUILabel() {

}

void FAGUILabel::updateShader() {
	delete shader;
	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
//	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);
}
