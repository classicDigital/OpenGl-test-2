#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include <iostream>
#include <vector>

#include "VertexBuffer.h"
#include "VertexArray.h"
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

int main(int argv, char** argc) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Callisto", NULL, NULL);
	glfwMakeContextCurrent(window); gladLoadGL();
	
	VertexBuffer vbo(vertexData.size() * sizeof(float), (void*)&vertexData[0], GL_STATIC_DRAW);
	VertexArray vao;

	vao.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0 * sizeof(float));
	vao.setAttributes(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));

	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	

/*=======================IMGUI================================*/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	
/*============================================================*/

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		int width;
		int height;
		glfwGetWindowSize(window, &width, &height);
		

		shader.enable();

		float time = (float)glfwGetTime();

		/*=======================IMGUI================================*/
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		bool isWireframe;

		ImGui::Begin("TEST");
		ImGui::Checkbox("Wireframe mode: ", &isWireframe);

		if (isWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		ImGui::End();

		/*============================================================*/

		
		glm::mat4x4 proj = glm::perspective(glm::radians(95.0f), (float)width / (float)height, 0.02f, 100.0f);
		glm::mat4 view = glm::rotate(glm::mat4(1), time, glm::vec3(0, 1, 1));
		glm::mat4 model = glm::rotate(glm::mat4(1), time, glm::vec3(1, 1, 0));
		
		glm::mat4x3 pvm = proj * view * model;
		shader.setUniformMat4("pvm", pvm, false);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glViewport(0, 0, width, height);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}