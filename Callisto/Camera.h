#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"

class Camera {
private:
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 camera_position;
	glm::vec3 camera_direction;
	glm::vec3 camera_target;
	glm::vec3 camera_up;
	glm::vec3 camera_right;
public:
	Camera(float fov, float aspect, float near, float far);
};

#endif