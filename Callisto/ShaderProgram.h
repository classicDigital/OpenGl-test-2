#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

class Shader {
private:
	std::string getFile(const char* PATH);
	GLint isCompiled = 0;
	GLint isValid = 0;
public:
	GLuint ID = 0;
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void enable();
	void disable();
	void del();

	void setUniformInt(const char* variableName, GLint value);
	void setUniformFloat(const char* variableName, GLfloat value);
	void setUniformBool(const char* variableName, GLboolean value);
	void setUniformMat2(const char* variableName, glm::mat2x2 matrix, GLboolean transpose);
	void setUniformMat3(const char* variableName, glm::mat3x3 matrix, GLboolean transpose);
	void setUniformMat4(const char* variableName, glm::mat4x4 matrix, GLboolean transpose);
};

#endif
