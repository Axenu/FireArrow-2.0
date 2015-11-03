#include <FA/FAGUIText.h>

FAGUIText::FAGUIText() {
	mesh = new FAMesh("square");
	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);
}

FAGUIText::FAGUIText(FAFont *font) {
	mesh = new FAMesh("square");

	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);

	this->font = font;
}

void FAGUIText::setText(std::string text) {
	this->text = text;
}

std::string FAGUIText::getText() {
	return this->text;
}

void FAGUIText::onUpdate(float dt) {

}

void FAGUIText::renderCharacter(int character, float x, float y, float charWidth, float charHeigth) {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, font->texture[character]);
    
    glUseProgram(shader->shaderProgram);

    glUniform3f(positionLocation, x + this->globalTransformation.x*2-1, -y + this->globalTransformation.y*2-1, 0);
    glUniform2f(sizeLocation, charWidth, charHeigth);

    this->mesh->render();
	
}

void FAGUIText::onRender() {
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glDisable(GL_CULL_FACE);
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
        renderCharacter(text[i], (pen_x + slot->bitmap_left)/(float)this->font->windowWidth, (slot->bitmap.rows - slot->bitmap_top)/(float)this->font->windowHeight, (slot->bitmap.width)/(float)this->font->windowWidth, slot->bitmap.rows/(float)this->font->windowHeight);
        pen_x += slot->advance.x >> 6;
        pen_y += slot->advance.y >> 6;
    }
}

FAGUIText::~FAGUIText() {

}

void FAGUIText::updateShader() {
	delete shader;
	this->shader = new FAShader("FAText");
	glUseProgram(this->shader->shaderProgram);

	//get uniforms
	this->positionLocation = glGetUniformLocation(this->shader->shaderProgram, "position");
	this->sizeLocation = glGetUniformLocation(this->shader->shaderProgram, "size");

	glUseProgram(0);
}
