#include <FA/FAShader.h>

FAShader::FAShader() {
	shaderProgram = -1;
}

FAShader::FAShader(std::string file) : FAShader(file, file) {
}

FAShader::FAShader(std::string vert, std::string frag) {
	GLint vertShader = createShader("/Users/Axenu/Developer/FireArrow-2.0/resources/shaders/" + vert + ".vert", GL_VERTEX_SHADER);
	GLint fragShader = createShader("/Users/Axenu/Developer/FireArrow-2.0/resources/shaders/" + frag + ".frag", GL_FRAGMENT_SHADER);
	name = vert;
	
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

FAShader::FAShader(std::string vert, std::string geom, std::string frag) {
	GLint vertShader = createShader("/Users/Axenu/Developer/FireArrow-2.0/resources/shaders/" + vert + ".vert", GL_VERTEX_SHADER);
	GLint fragShader = createShader("/Users/Axenu/Developer/FireArrow-2.0/resources/shaders/" + frag + ".frag", GL_FRAGMENT_SHADER);
	GLint geomShader = createShader("/Users/Axenu/Developer/FireArrow-2.0/resources/shaders/" + geom + ".geom", GL_GEOMETRY_SHADER);
	name = vert;
	
	shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertShader);
	if (geomShader != -1) {glAttachShader(shaderProgram, geomShader);}
	glAttachShader(shaderProgram, fragShader);
	
	glBindFragDataLocation(shaderProgram, 0, "Frag_Data");
	
	glLinkProgram(shaderProgram);
	glDeleteShader(vertShader);
	if (geomShader != -1) {glDeleteShader(geomShader);}
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

FAShader::FAShader(std::string *vertexShader, std::string *fragmentShader) {
	GLint vertShader = createShaderFromString(vertexShader, GL_VERTEX_SHADER);
	GLint fragShader = createShaderFromString(fragmentShader, GL_FRAGMENT_SHADER);
	name = "Material shader";
	
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

void FAShader::printListOfUniforms() {
    std::cout << "Printing program uniforms: " << std::endl;
    int total = -1;
    glGetProgramiv( shaderProgram, GL_ACTIVE_UNIFORMS, &total ); 
    for(int i=0; i<total; ++i)  {
        int name_len=-1, num=-1;
        GLenum type = GL_ZERO;
        char name[100];
        glGetActiveUniform( shaderProgram, GLuint(i), sizeof(name)-1,
            &name_len, &num, &type, name );
        name[name_len] = 0;
        std::cout << name << std::endl;
        // GLuint location = glGetUniformLocation( shaderProgram, name );
    }
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
        std::cout << source << std::endl;
        
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

GLint FAShader::createShaderFromString(std::string *shader, GLenum shaderType) const {
	GLuint shaderID = glCreateShader(shaderType);
    
    const GLchar *shaderSource = shader->c_str();
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    
    glCompileShader(shaderID);
    
    GLint compileStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        std::cout << "Shader failed to compile: '" << shader << "'" << std::endl;
        std::cout << *shader << std::endl;
        
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