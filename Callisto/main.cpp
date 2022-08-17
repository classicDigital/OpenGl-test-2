#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"

std::vector<GLfloat> vertexData = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,// top left
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,// bottom right
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f // top right
};

std::vector<GLuint> indices = {
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

	VertexBuffer vbo(vertexData.size() * sizeof(float), (void*)&vertexData[0], GL_STATIC_DRAW);
	ElementBuffer ebo(sizeof(indices), &indices, GL_STATIC_DRAW);
	VertexArray vao;

	vao.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0 * sizeof(float));
	vao.setAttributes(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float));

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

	Texture tex1("res/night_bliss.jpg", true);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		shader.enable();

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indices[0]);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}