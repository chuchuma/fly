#include <stdio.h>
#include "display.h"

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

void displayMode() {
	glfwSetErrorCallback(errorCallback);
}
void errorCallback(int error, const char* description) {
	fputs(description, stderr);	
}
void displayFunc(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);		
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}
