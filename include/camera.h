#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
typedef int camera_dir_t;

class Camera {
public:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat mvtSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;
    Camera(glm::vec3 _pos, glm::vec3 _worldUp, GLfloat _yaw, GLfloat _pitch, GLfloat _mvtSpeed, GLfloat _mouseSensitivity, GLfloat _zoom);
    ~Camera();
    glm::mat4 getViewMatrix();
    void processTime(GLFWwindow* window, GLfloat deltaT);
    void processMouseMvt(GLfloat xoffset, GLfloat yoffset);
    void processMouseScroll(GLfloat yoffset);
private:
    void updateCameraVec();
};
