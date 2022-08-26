#include "Camera.h"

Camera::Camera(float fov, float aspect, float near, float far) {
	camera_position = glm::vec3(0.0f, 0.0f, -3.0f);
	camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera_direction = glm::normalize(camera_position - camera_target);

	camera_right = glm::normalize(glm::cross(camera_direction, up));
	camera_up = glm::normalize(glm::cross(camera_direction, camera_right));

	//glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, near, far);
	//glm::mat4 view;
}