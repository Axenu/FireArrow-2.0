#include <FA/FAMesh.h>

FAMesh::FAMesh() {

}

FAMesh::FAMesh(std::string path) {
	int place = path.find_last_of(".");
    if (place != std::string::npos) {
        std::string filetype = path.substr(place+1, path.length());
        if (filetype == "fa"){
            loadFAModel("/Users/Axenu/Developer/FireArrow 2.0/resources/models/" + path);
        }
    } else {
        loadFAModel("/Users/Axenu/Developer/FireArrow 2.0/resources/models/" + path);
    }
}

FAMesh::FAMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, bool hasNormal, bool hasColor) {

    this->_hasColor = hasColor;
    this->_hasNormal = hasNormal;

    // load model to graphicscard
    this->numberOfVertices = indices.size();

    //test
    // GLfloat vertA[] = {0,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,1,0, 1,0,0, 1,0,0, 0,1,0, 1,0,0, 1,0,0};
    // GLuint indA[] = {0,1,2,0,2,3};
    // _hasColor = true;
    // _hasNormal = true;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    int attributes = 3;
    if (_hasNormal) attributes +=3;
    if (_hasColor) attributes +=3;

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
    int offset = 3;
    if (_hasNormal) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (offset * sizeof(GLfloat)));
        offset += 3;
    }
    if (_hasColor) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (offset * sizeof(GLfloat)));
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void FAMesh::loadFAModel(std::string path) {
    std::ifstream file (path);
    std::vector<glm::vec3> vertexArray;
    std::vector<glm::vec3> normalArray;
    std::vector<int> colorArray;
    std::vector<glm::vec3> materialArray;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    
    if (file.is_open() && file.is_open()) {
        
        while (!file.eof()) {
            
            std::string f;
            int count;
            file >> f;
            if (f == "v") {
                file >> count;
                vertexArray = std::vector<glm::vec3>();
                glm::vec3 vec;
                for (int i = 0; i < count; i++) {
                    file >> vec.x >> vec.y >> vec.z;
                    vertexArray.push_back(vec);
                }
            } else if (f == "n") {
                _hasNormal  = true;
                file >> count;
                normalArray = std::vector<glm::vec3> ();
                glm::vec3 normal;
                for (int i = 0; i < count; i++) {
                    file >> normal.x >> normal.y >> normal.z;
                    normalArray.push_back(normal);
                }
            } else if (f == "c") {
                _hasColor = true;
                file >> count;
                int index;
                for (int i = 0; i < count; i++) {
                    file >> index;
                    colorArray.push_back(index);
                }
            } else if (f == "m") {
                file >> count;
                glm::vec3 color;
                for (int i = 0; i < count; i++) {
                    file >> color.x >> color.y >> color.z;
                    materialArray.push_back(color);
                }
            } else if (f == "i") {
                file >> count;
                indices = std::vector<GLuint> ();
                vertices = std::vector<GLfloat> ();
                for (int i = 0; i < count * 3; i++) {
                    indices.push_back(i);
                }
                float v1, v2, v3, n;
                for (int i = 0; i < count; i++) {
                    file >> v1 >> v2 >> v3;
                    if (_hasNormal) {
                        file >> n;
                    }
                    int face = 0;
                    if (_hasColor) {
                        face = colorArray[n];
                    }
                    
                    vertices.push_back(vertexArray[v1].x);
                    vertices.push_back(vertexArray[v1].y);
                    vertices.push_back(vertexArray[v1].z);
                    if (_hasNormal) {
                        vertices.push_back(normalArray[n].x);
                        vertices.push_back(normalArray[n].y);
                        vertices.push_back(normalArray[n].z);
                    }
                    if (_hasColor) {
                        vertices.push_back(materialArray[face].x);
                        vertices.push_back(materialArray[face].y);
                        vertices.push_back(materialArray[face].z);
                    }
                    
                    vertices.push_back(vertexArray[v2].x);
                    vertices.push_back(vertexArray[v2].y);
                    vertices.push_back(vertexArray[v2].z);
                    if (_hasNormal) {
                        vertices.push_back(normalArray[n].x);
                        vertices.push_back(normalArray[n].y);
                        vertices.push_back(normalArray[n].z);
                    }
                    if (_hasColor) {
                        vertices.push_back(materialArray[face].x);
                        vertices.push_back(materialArray[face].y);
                        vertices.push_back(materialArray[face].z);
                    }
                    
                    vertices.push_back(vertexArray[v3].x);
                    vertices.push_back(vertexArray[v3].y);
                    vertices.push_back(vertexArray[v3].z);
                    if (_hasNormal) {
                        vertices.push_back(normalArray[n].x);
                        vertices.push_back(normalArray[n].y);
                        vertices.push_back(normalArray[n].z);
                    }
                    if (_hasColor) {
                        vertices.push_back(materialArray[face].x);
                        vertices.push_back(materialArray[face].y);
                        vertices.push_back(materialArray[face].z);
                    }
                }
            } else {
                std::cout << "Unknown character! asuming it's a comment: \"" << f << "\"" << std::endl;
            }
        }

        // load model to graphicscard
        this->numberOfVertices = indices.size();

        //test
        // GLfloat vertA[] = {0,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,1,0, 1,0,0, 1,0,0, 0,1,0, 1,0,0, 1,0,0};
        // GLuint indA[] = {0,1,2,0,2,3};
        // _hasColor = true;
        // _hasNormal = true;

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        int attributes = 3;
        if (_hasNormal) attributes +=3;
        if (_hasColor) attributes +=3;

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (0 * sizeof(GLfloat)));
        int offset = 3;
        if (_hasNormal) {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (offset * sizeof(GLfloat)));
            offset += 3;
        }
        if (_hasColor) {
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, attributes * sizeof(GLfloat), (GLvoid *) (offset * sizeof(GLfloat)));
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    } else {
        std::cout << "FAModel failed to load model: " << path << std::endl;
    }
}

void FAMesh::render() const {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, numberOfVertices, GL_UNSIGNED_INT, NULL);
}

bool FAMesh::hasVertexNormal() {
    return this->_hasNormal;
}

bool FAMesh::hasVertexColor() {
    return this->_hasColor;
}

FAMesh::~FAMesh() {

}










