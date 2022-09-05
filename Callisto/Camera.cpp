#include "Camera.h"

Camera::Camera(glm::vec3 position) {
	Camera::position = position;
}

void Camera::matrix(Shader& shader, float FOV, float near, float far, int width, int height) {
	glm::mat4 projection = glm::perspective(glm::radians(FOV), (float)width / (float)height, near, far);
	glm::mat4 view = glm::lookAt(position, position + front, up);

	shader.setUniformMat4("proj", projection, false);
	shader.setUniformMat4("view", view, false);
}

void Camera::input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += speed * front;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position += speed * -front;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position += speed * glm::normalize(glm::cross(up, front));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += speed * glm::normalize(glm::cross(front, up));
	}
}
