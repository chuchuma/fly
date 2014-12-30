#include "mesh.h"

Mesh::Mesh(const vector<Vertex> &_vertices, const vector<GLuint> &_indices, const vector<Texture> &_textures):
    vertices(_vertices),
    indices(_indices),
    textures(_textures)
{
    setupMesh();
}
Mesh::~Mesh() {
}
void Mesh::draw(GLuint shaderProgram) {
    GLuint diffuseNum = 1;
    GLuint specularNum = 1;
    for (GLuint i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        stringstream ss;
        string num;
        string name = textures[i].type;
        if (name == "texture_diffuse") {
            ss << diffuseNum++;
        } else if (name == "texture_specular") {
            ss << specularNum++;
        }
        num = ss.str();
        glGetUniformLocation(shaderProgram, ("material." + name + num).c_str());
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, norm));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}
