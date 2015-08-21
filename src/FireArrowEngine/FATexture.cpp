#include <FA/FATexture.h>

FATexture::FATexture() {

}

FATexture::FATexture(const GLchar *path) {

}

FATexture::~FATexture() {

}

GLuint FATexture::createTexture(const GLchar *path) {
    
    ILuint image = ilGenImage();
    ilBindImage(image);
    ILboolean loadSucsess = ilLoadImage(path);
    if (!loadSucsess) {
        ilBindImage(0);
        std::cout << "File not found: '" << path << "'" << std::endl;
        ilDeleteImage(image);
        return 0;
    }
    
    ILboolean convertSuccess = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    if (!convertSuccess) {
        ilBindImage(0);
        std::cout << "Failed to conver image: '" << path << "'" << std::endl;
        ilDeleteImage(image);
        return 0;
    }
    
    GLuint texture;
    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
    glBindTexture(GL_TEXTURE_2D, 0);
    
    ilBindImage(0);
    ilDeleteImage(image);
    return texture;
}
