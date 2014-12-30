#include <string>
using std::string;
struct Texture {
    GLuint id;
    string type;
    const char* path;
};
Texture getTexture(const char* path, string directory, string typeName);
