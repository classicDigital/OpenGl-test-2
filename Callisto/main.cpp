#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "ShaderProgram.h"

GLfloat vertexData[] = {
	-0.5f, -0.5f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, // top left
	 0.5f, -0.5f, 0.0f, // bottom right
	 0.5f,  0.5f, 0.0f  // top right
};

GLuint indices[] = {
	0, 1, 2,
	3, 2, 1
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
	ElementBuffer ebo(sizeof(indices), &indices, GL_STATIC_DRAW);
	VertexArray vao;

	vao.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");


	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		shader.enable();

		double time = glfwGetTime();
		shader.setUniformFloat("time", time);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indices);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}