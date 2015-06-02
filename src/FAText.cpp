#include "FAText.h"

FAText::FAText() {
	mesh = new FAMesh("square");
	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);
}

FAText::FAText(FAFont *font) {
	mesh = new FAMesh("square");

	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);

	this->font = font;
}

void FAText::setText(std::string text) {
	this->text = text;
}

std::string FAText::getText() {
	return this->text;
}

void FAText::update(float dt) {

}

void FAText::renderCharacter(int character, float x, float y, float charWidth, float charHeigth) {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font->texture[character]);
    
    glUseProgram(shader->shaderProgram);

    glUniform3f(positionLocation, x + this->position.x * 2, y - this->position.y * 2, this->position.z);
    glUniform2f(sizeLocation, charWidth, charHeigth);

    this->mesh->render();
	
}

void FAText::render() {
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int pen_x = 0, pen_y = 0;
    FT_GlyphSlot slot = font->face->glyph;
    for (int i = 0; i < text.length(); i++ ) {
        FT_UInt  glyph_index;
        glyph_index = FT_Get_Char_Index( font->face, text[i] );
        int error = FT_Load_Glyph( font->face, glyph_index, FT_LOAD_DEFAULT );
        if ( error )
            continue;
        error = FT_Render_Glyph( slot, FT_RENDER_MODE_NORMAL );
        if ( error )
            continue;
        
        renderCharacter(text[i], (pen_x + slot->bitmap_left)/(float)this->font->windowWidth, (pen_y - slot->bitmap_top)/(float)this->font->windowHeight, (slot->bitmap.width)/(float)this->font->windowWidth, slot->bitmap.rows/(float)this->font->windowHeight);
        pen_x += slot->advance.x >> 6;
        pen_y += slot->advance.y >> 6;
    }
}

FAText::~FAText() {

}

void FAText::updateShader() {
	delete shader;
	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);
}
