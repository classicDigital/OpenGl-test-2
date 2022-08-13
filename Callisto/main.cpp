#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

GLfloat vertexData[] = {
	-0.5f, -0.5f, 0.0f, // bottom left
	 0.0f,  0.5f, 0.0f, // top
	 0.5f, -0.5f, 0.0f // bottom right
};

int main(int argv, char** argc) {

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Callisto", NULL, NULL);
	glfwMakeContextCurrent(window); gladLoadGL();

	glViewport(0, 0, 800, 600);

	VertexBuffer vbo(sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	VertexArray vao;

	vao.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {

		shader.enable();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}