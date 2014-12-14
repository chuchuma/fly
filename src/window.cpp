#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "display.h"

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#ifndef NULL
#define NULL (0)
#endif

static GLFWwindow* window;

void windowInit() {
	glfwInit();
	window = glfwCreateWindow(500, 500, "Fly", NULL, NULL);
	if (!window) {
		glfwTerminate();
		puts("HI");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	displayMode();
}

void windowMainLoop() {
	while (!glfwWindowShouldClose(window)) {
		displayFunc(window);
		glfwSwapBuffers(window);	
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
