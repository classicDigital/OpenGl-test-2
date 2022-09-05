#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderProgram.h"

class Camera {
public:
	glm::vec3 position;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width;
	int height;

	float speed = 0.01f;
	float sensitivity = 100.0f;

	Camera(glm::vec3 position);

	void matrix(Shader& shader, float FOV, float near, float far, int width, int height);
	void input(GLFWwindow* window);
};

#endif