#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "display.h"

extern GLuint shaderProgram;
static GLuint VAO;

Camera* camera;

void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
    }
}
static GLdouble lastTime;
void displayMode(GLFWwindow* window) {
	glfwSetErrorCallback(errorCallback);
    ensureShaders(TEST_VS, TEST_FRAG);
    ensureModel(SUIT);
    glfwSetKeyCallback(window, keyFunc);

    glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
    glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
    GLfloat yaw = -90;
    GLfloat pitch = 0;
    GLfloat moveSpeed = 5;
    // TODO configurable mouse sensistivity
    GLfloat mouseSensitivity = 0.25f;
    GLfloat zoom = 45;
    camera = new Camera(
        cameraPos, 
        cameraUp, 
        yaw, 
        pitch, 
        moveSpeed, 
        mouseSensitivity, 
        zoom
    );

    lastTime = 0;
    glfwSetTime(lastTime);
}
void errorCallback(int error, const char* description) {
    fputs(description, stderr);
}
void displayFunc(GLFWwindow* window) {
    glClearColor(0.05, 0.05, 0.05, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);

    glm::mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
    glm::mat4 view = camera->getViewMatrix();

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0, -1.75, 0.0));
    model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    GLdouble currentTime = glfwGetTime();
    GLdouble diffTime = currentTime - lastTime;
    camera->processTime(window, diffTime);
    lastTime = currentTime;
    drawModel(SUIT);
}
