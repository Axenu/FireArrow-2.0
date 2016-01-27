#include <FA/FAGUILabel.h>

FAGUILabel::FAGUILabel() {
	mesh = new FAMesh("square");
	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);
}

FAGUILabel::FAGUILabel(FAFont *font) {
	mesh = new FAMesh("square");

	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);

	this->font = font;
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
		vertices.push_back(x);
		vertices.push_back(0);
		//v1 |-
		vertices.push_back(x);
		vertices.push_back(g.height);
		//v2-|
		vertices.push_back(x + g.width);
		vertices.push_back(g.height);
		
		
		//v3
		vertices.push_back(x);
		vertices.push_back(g.height);
		//v4
		vertices.push_back(x);
		vertices.push_back(g.height);
		//v5
		vertices.push_back(x);
		vertices.push_back(g.height);
		x += g.xAdvance;
	}
	
	
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	
//	int attributes = 3;
//	if (_hasNormal) attributes +=3;
//	if (_hasColor) attributes +=3;
//	
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
//	int offset = 3;
//	if (_hasNormal) {
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (offset * sizeof(GLfloat)));
//		offset += 3;
//	}
//	if (_hasColor) {
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (offset * sizeof(GLfloat)));
//	}
//	
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
	
}

std::string FAGUILabel::getText() {
	return this->text;
}

void FAGUILabel::onUpdate(float dt) {

}

void FAGUILabel::renderCharacter(int character, float x, float y, float charWidth, float charHeigth) {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font->texture[character]);
    
    glUseProgram(shader->shaderProgram);

    glUniform3f(positionLocation, x + this->globalTransformation.x*2-1, -y + this->globalTransformation.y*2-1, 0);
    glUniform2f(sizeLocation, charWidth, charHeigth);

    this->mesh->render();
	
}

void FAGUILabel::onRender() {
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glDisable(GL_CULL_FACE);
//    int pen_x = 0, pen_y = 0;
//    FT_GlyphSlot slot = font->face->glyph;
//    for (int i = 0; i < text.length(); i++ ) {
//        FT_UInt  glyph_index;
//        glyph_index = FT_Get_Char_Index( font->face, text[i] );
//        int error = FT_Load_Glyph( font->face, glyph_index, FT_LOAD_DEFAULT );
//        if ( error )
//            continue;
//        error = FT_Render_Glyph( slot, FT_RENDER_MODE_NORMAL );
//        if ( error )
//            continue;
////        renderCharacter(text[i], (pen_x + slot->bitmap_left)/(float)this->font->windowWidth, (slot->bitmap.rows - slot->bitmap_top)/(float)this->font->windowHeight, (slot->bitmap.width)/(float)this->font->windowWidth, slot->bitmap.rows/(float)this->font->windowHeight);
//        pen_x += slot->advance.x >> 6;
//        pen_y += slot->advance.y >> 6;
//    }
	
	glUseProgram(shader->shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font->fontTexture);
	
	glyph g = font->glyphs[(int)text[0]];
	float x = 0.0;
	
	for (int i = 0; i < text.length(); i++) {
		
		
		glUniform3f(positionLocation, 0, 0, 0);
		glUniform2f(sizeLocation, g.width, g.height);
		
		this->mesh->render();
		x += g.xAdvance;
	}
	
}

FAGUILabel::~FAGUILabel() {

}

void FAGUILabel::updateShader() {
	delete shader;
	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);
}
