#include <GL/glew.h>
#include "camera.h"
Camera::Camera(glm::vec3 _pos, glm::vec3 _worldUp, GLfloat _yaw, GLfloat _pitch, GLfloat _mvtSpeed, GLfloat _mouseSensitivity, GLfloat _zoom) :
    pos(_pos),
    worldUp(_worldUp),
    yaw(_yaw),
    pitch(_pitch),
    mvtSpeed(_mvtSpeed),
    mouseSensitivity(_mouseSensitivity),
    zoom(_zoom)
{
    updateCameraVec();
}
Camera::~Camera() {
}
glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(pos, pos + front, worldUp);
}
#define FORWARD 'W'
#define BACKWARD 'S'
#define LEFT 'A'
#define RIGHT 'D'
void Camera::processTime(GLFWwindow* window, GLfloat deltaTime) {
    GLfloat velocity = mvtSpeed * deltaTime;
    if (glfwGetKey(window, FORWARD) != GLFW_RELEASE) {
        pos += front * velocity;
    }
    if (glfwGetKey(window, BACKWARD) != GLFW_RELEASE) {
        pos -= front * velocity;
    }
    if (glfwGetKey(window, LEFT) != GLFW_RELEASE) {
        pos -= right * velocity;
    }
    if (glfwGetKey(window, RIGHT) != GLFW_RELEASE) {
        pos += right * velocity;
    }
}
void Camera::processMouseMvt(GLfloat xoffset, GLfloat yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0) {
        pitch = 89.0;
    }
    if (pitch < -89.0) {
        pitch = -89.0;
    }
    updateCameraVec();
}
void Camera::processMouseScroll(GLfloat yoffset) {
    if (zoom >= 1.0 && zoom <= 45.0) {
        zoom -= yoffset;
    }
    if (zoom <= 1.0) {
        zoom = 1.0;
    }
    if (zoom >= 45.0) {
        zoom = 45.0;
    }
}
void Camera::updateCameraVec() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
