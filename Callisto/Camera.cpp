#include "Camera.h"

Camera::Camera(int width, int height) {
	Camera::width = width;
	Camera::height = height;
	//Camera::position = position;
	Camera::aspect = (float)width / (float)height;
}

void Camera::matrix(Shader shader, float fov, float near, float far) {
	glm::mat4 proj = glm::perspective(glm::radians(fov), aspect, near, far);
	glm::mat4 view = glm::lookAt(position, position + orientation, up);

	shader.setUniformMat4("proj", proj, false);
	shader.setUniformMat4("view", view, false);
}

void Camera::input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position += speed * -up;
	}
}