#include "FAShader.h"

FAShader::FAShader() {
	shaderProgram = -1;
}

FAShader::FAShader(std::string file) {
	GLint vertShader = createShader("/Users/Axenu/Developer/clang++/first/resources/shaders/" + file + ".vert", GL_VERTEX_SHADER);
	GLint fragShader = createShader("/Users/Axenu/Developer/clang++/first/resources/shaders/" + file + ".frag", GL_FRAGMENT_SHADER);
	name = file;
	
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	
	glBindFragDataLocation(shaderProgram, 0, "Frag_Data");
	
	glLinkProgram(shaderProgram);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
	
	GLint linkStatus;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		std::cout << "Shader program failed to link!" << std::endl;
		
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, infoLog);
		std::cout << infoLog << std::endl;
		delete[] infoLog;
	}
}

FAShader::FAShader(std::string vert, std::string frag) {
	// GLint vertShader = createShader("../resources/shaders/" + vert, GL_VERTEX_SHADER);
 //    GLint fragShader = createShader("../resources/shaders/" + frag, GL_FRAGMENT_SHADER);
	
	// std::string s = vert;
	// if (s.length() > 5) {
	// 	s.erase(s.end() - 5, s.end());
	// 	name = s;
	// }
	
 //    shaderProgram = glCreateProgram();
    
 //    glAttachShader(shaderProgram, vertShader);
 //    glAttachShader(shaderProgram, fragShader);
    
 //    glBindFragDataLocation(shaderProgram, 0, "Frag_Data");
    
 //    glLinkProgram(shaderProgram);
 //    glDeleteShader(vertShader);
 //    glDeleteShader(fragShader);
    
 //    GLint linkStatus;
 //    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
 //    if (linkStatus != GL_TRUE) {
 //        std::cout << "Shader program failed to link!" << std::endl;
        
 //        GLint infoLogLength;
 //        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
 //        GLchar *infoLog = new GLchar[infoLogLength + 1];
 //        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, infoLog);
 //        std::cout << infoLog << std::endl;
 //        delete[] infoLog;
 //    }
}

GLint FAShader::createShader(std::string path, GLenum shaderType) const {
    std::fstream fin;
    GLuint shaderID = glCreateShader(shaderType);
    
    // Vertex Shader
    fin.open(path);
    if(!fin.is_open()) {
        fin.close();
        std::cout << "File not found: '" << path << "'" << std::endl;
        return 0;
    }
    
    std::string source((std::istreambuf_iterator<GLchar>(fin)), std::istreambuf_iterator<GLchar>());
    fin.close();
    
    const GLchar *shaderSource = source.c_str();
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    
    glCompileShader(shaderID);
    
    GLint compileStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        std::cout << "Shader failed to compile: '" << path << "'" << std::endl;
        
        GLint infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);
        std::cout << infoLog << std::endl;
        delete[] infoLog;
        return 0;
    }
    return shaderID;
}

FAShader::~FAShader() {
    glUseProgram(0);
    glDeleteProgram(shaderProgram);
}