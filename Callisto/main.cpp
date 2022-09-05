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
#include "Camera.h"

void framebuffer_callback(GLFWwindow* winodw, int width, int height) {
	glViewport(0, 0, width, height);
}

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

int main() {
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	int width = 800;
	int height = 600;

	bool isWireframe = false;
	float fieldOfView = 95.0f;

	shader.enable();
	Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwSetFramebufferSizeCallback(window, framebuffer_callback);
		glfwGetWindowSize(window, &width, &height);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Box");
			ImGui::Checkbox("Wireframe mode: ", &isWireframe);
			ImGui::SliderFloat("FOV", &fieldOfView, 0.0f, 120.0f);

			if (isWireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		ImGui::End();

		camera.matrix(shader, fieldOfView, 0.01f, 100.0f, width, height);
		camera.input(window);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}