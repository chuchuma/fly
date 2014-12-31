#include "camera.h"

#include <assert.h>

#include <map>
using std::map;

map<int, int> keysPressed;

int glfwGetKey(GLFWwindow* window, int key) {
    return keysPressed[key];
}

int main() {
    glm::vec3 pos(0,0,0);
    glm::vec3 up(0,1,0);
    GLfloat yaw(-90);
    GLfloat pitch(0);
    GLfloat speed(1);
    GLfloat sensitivity(0);
    GLfloat zoom(1);
    Camera camera(pos, up, yaw, pitch, speed, sensitivity, zoom);

    // no keys pressed
    for (int ch = 0; ch < 256; ch++) {
        keysPressed[ch] = GLFW_RELEASE;
    }

    glm::mat4 before, after;
    before = camera.getViewMatrix();
    camera.processTime(NULL, 0);
    after = camera.getViewMatrix();
    assert(before == after);

    camera.processTime(NULL, 1);
    after = camera.getViewMatrix();
    assert(before == after);

    return 0;
}
