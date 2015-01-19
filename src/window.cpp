#include <stdlib.h>
#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OVR_CAPI.h"

#include "window.h"

#ifndef NULL
#define NULL (0)
#endif

static GLFWwindow* window;

ovrHmd hmd;
void windowInit() {
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    // HMD
    ovr_Initialize();
    hmd = ovrHmd_Create(0);
    if (hmd) {
        ovrSizei resolution = hmd->Resolution;
    } else {
        fputs("No head mounted display.\n", stderr);
    }


    // Window
    window = glfwCreateWindow(500, 500, "Fly", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    displayMode(window);
}

void windowMainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        displayFunc(window);
        glfwSwapBuffers(window);	
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    ovrHmd_Destroy(hmd);
    ovr_Shutdown();

    exit(EXIT_SUCCESS);
}
