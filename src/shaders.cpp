#define GLEW_STATIC 
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "capitalC.h"
#include "shaders.h"

GLuint shaderProgram;
char const *const vertex_shader_paths[1] = {
    "shaders/test_shader.vs"
};
char const *const fragment_shader_paths[1] = {
    "shaders/test_shader.frag"
};
bool ensureShaders(vertex_shader_t vs, fragment_shader_t frag) {
    const char* vsPath = vertex_shader_paths[vs];
    const char* fragPath = fragment_shader_paths[frag];
    int vsFd = Open(vsPath, O_RDONLY);
    int fragFd = Open(fragPath, O_RDONLY);
    struct stat st;
    Fstat(vsFd, &st);
    size_t vsSize = st.st_size;
    Fstat(fragFd, &st);
    size_t fragSize = st.st_size;
    GLchar* vsCode = (GLchar*) Malloc(vsSize + 1);
    GLchar* fragCode = (GLchar*) Malloc(fragSize + 1);
    Read(vsFd, vsCode, vsSize);
    vsCode[vsSize] = '\0';
    Read(fragFd, fragCode, fragSize);
    fragCode[fragSize] = '\0';
    Close(vsFd);
    Close(fragFd);
    puts(vsCode);
    puts(fragCode);
    //Compile Shaders
    GLuint vertex, fragment;
    GLint success;
    int logBufLen = 512;
    GLchar infoLog[logBufLen];
    //Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vsCode, NULL);
    Free(vsCode);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, logBufLen, NULL, infoLog);
        fputs(infoLog, stderr);
        return false;
    }
    //Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragCode, NULL);
    Free(fragCode);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, logBufLen, NULL, infoLog);
        fputs(infoLog, stderr);
        return false;
    }
    //Shader Program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, logBufLen, NULL, infoLog);
        fputs(infoLog, stderr);
        return false;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

