#include <stdio.h>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include "display.h"

extern GLuint shaderProgram;
static GLuint VAO;
void displayMode() {
	glfwSetErrorCallback(errorCallback);
    ensureShaders(TEST_VS, TEST_FRAG);
    ensureModel(TEST);
    GLfloat vertices[] = {
        0.5, 0.0, 
        -0.5, 0.5,
        0.0, 0.5
    };
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0); //unbind vertex array
}
void errorCallback(int error, const char* description) {
    fputs(description, stderr);
}
void displayFunc(GLFWwindow* window) {
    glClearColor(0.2, 0.3, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
