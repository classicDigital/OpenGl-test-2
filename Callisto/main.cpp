#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "ShaderProgram.h"


std::vector<GLfloat> vertexData = {
	-0.5f, -0.5f, 0.5f,// bottom left  front 0
	-0.5f,  0.5f, 0.5f,// top left     front 1
	 0.5f, -0.5f, 0.5f,// bottom right front 2
	 0.5f,  0.5f, 0.5f,// top right	   front 3

	-0.5f, -0.5f,-0.5f,// bottom left  back 4
	-0.5f,  0.5f,-0.5f,// top left     back 5
	 0.5f, -0.5f,-0.5f,// bottom right back 6
	 0.5f,  0.5f,-0.5f // top right    back 7
};

std::vector<GLuint> indices = {
	0, 1, 2, // front
	3, 2, 1,
	4, 5, 6, // back
	7, 6, 5,
	2, 3, 6, // right
	7, 6, 3,
	0, 1, 4, // left
	5, 4, 1
};

int main(int argv, char** argc) {

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(600, 600, "Callisto", NULL, NULL);
	glfwMakeContextCurrent(window); gladLoadGL();

	glViewport(0, 0, 600, 600);

	VertexBuffer vbo(vertexData.size() * sizeof(float), (void*)&vertexData[0], GL_STATIC_DRAW);
	ElementBuffer ebo(sizeof(indices), &indices, GL_STATIC_DRAW);
	VertexArray vao;

	vao.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0 * sizeof(float));

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

	glEnableVertexAttribArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) {
		shader.enable();

		glm::mat4x4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -2.0f, 1.0f);
		glm::mat4 view = glm::rotate(glm::mat4(1), (float)glfwGetTime(), glm::vec3(0, 1, 1));
		glm::mat4x4 model = glm::mat4(1);

		glm::mat4x3 pvm = proj * view * model;

		shader.setUniformMat4("pvm", pvm, false);

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}