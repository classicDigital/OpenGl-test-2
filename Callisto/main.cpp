#include <iostream>
#include <GLFW/glfw3.h>

int main(int argv, char** argc) {

	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Calisto", NULL, NULL);
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}