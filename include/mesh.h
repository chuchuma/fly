#include <string>
#include <sstream>
#include <vector>

#include <assimp/types.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "textures.h"

using std::string;
using std::stringstream;
using std::vector;
struct Vertex {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 texCoords;
};
class Mesh {
public:
    const vector<Vertex> vertices;
    const vector<GLuint> indices;
    const vector<Texture> textures; 
    Mesh(const vector<Vertex> &vertices, const vector<GLuint> &indices, const vector<Texture> &textures);
    ~Mesh();
    void draw(GLuint shaderProgram);
private:
    GLuint VAO, VBO, EBO;
    void setupMesh();
};
