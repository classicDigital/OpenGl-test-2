#define STB_IMAGE_IMPLEMENTATION

#define WIDTH 800
#define HEIGHT 600

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
	// FRONT
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f, // BR
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f, // TR
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f, // BL

	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f, // TL
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f, // BL
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f, // TR

	// BACK
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f, // BL
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f, // TL
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f, // BR

	 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f, // TR
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f, // BR
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f, // TL

	// LEFT
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f, // BLB
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f, // TLB
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f, // BLF

	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f, // TLF
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f, // BLF
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f, // TLB

	// RIGHT
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f, // BRF
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f, // TRF
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f, // BRB
	
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f, // TRB
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f, // BRB
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f, // TRF

	 // TOP
	-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f, // TLF
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f, // TLB
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f, // TRF

	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f, // TRB
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f, // TRF
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f, // TLB

	// BOTTOM
	 0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 1.0f, // BRF
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f, // BRB
	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 1.0f, // BLF

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f, // BLB
	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 1.0f, // BLF
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f, // BRB
};

/*
std::vector<GLuint> indices = {
	0, 1, 2, // front
	3, 2, 1,
	4, 6, 5, // back
	7, 5, 6,
	0, 1, 4, // left
	5, 4, 1,
	2, 3, 6, // right
	7, 6, 3,
	5, 1, 3, // top
	7, 3, 5,
	0, 4, 2, // bottom
	4, 6, 2
};
*/

float aspect = WIDTH / HEIGHT;

int main(int argv, char** argc) {

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Callisto", NULL, NULL);
	glfwMakeContextCurrent(window); gladLoadGL();

	glViewport(0, 0, WIDTH, HEIGHT);
	

	VertexBuffer vbo(vertexData.size() * sizeof(float), (void*)&vertexData[0], GL_STATIC_DRAW);
	VertexArray vao;

	vao.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0 * sizeof(float));
	vao.setAttributes(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// TODO : fix aspect ratio.

	while (!glfwWindowShouldClose(window)) {
		shader.enable();

		float time = (float)glfwGetTime();

		
		glm::mat4x4 proj = glm::perspective(glm::radians(95.0f), aspect, 0.02f, 100.0f);
		glm::mat4 view = glm::rotate(glm::mat4(1), time, glm::vec3(0, 1, 1));
		glm::mat4 model = glm::rotate(glm::mat4(1), time, glm::vec3(1, 1, 0));
		
		glm::mat4x3 pvm = proj * view * model;
		shader.setUniformMat4("pvm", pvm, false);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 64);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}