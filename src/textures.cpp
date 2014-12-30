#include <map>

#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include "textures.h"
using std::map;

map<const char*, Texture> textures;
Texture getTexture(const char* path, string directory, string typeName) {
    const char* filename = (directory + '/' + string(path)).c_str();
    if (textures.find(filename) != textures.end()) {
        return textures[filename];
    }
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height;
    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    Texture texture;
    texture.id = textureID;
    texture.type = typeName;
    texture.path = path;
    textures[path] = texture;
    return texture;
}
