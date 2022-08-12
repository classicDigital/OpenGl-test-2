#include "ShaderProgram.h"


std::string Shader::getFile(const char* PATH) {
	std::ifstream file;
	std::stringstream buffer;
	std::string data;

	file.open(PATH);
	buffer << file.rdbuf();
	file.close();
	data = buffer.str();
	return data;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	ID = glCreateProgram();
	
	std::string __vertexsrc = getFile(vertexShaderPath);
	std::string __fragmentsrc = getFile(fragmentShaderPath);

	const char* vertexData = __vertexsrc.c_str();
	const char* fragData = __fragmentsrc.c_str();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexData, nullptr);
	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		GLchar info[512];

		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
		glGetShaderInfoLog(vs, maxLength, &maxLength, &info[0]);

		std::cout << info << std::endl;

		glDeleteShader(vs);
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragData, nullptr);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		GLchar info[512];

		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
		glGetShaderInfoLog(fs, maxLength, &maxLength, &info[0]);

		std::cout << info << std::endl;

		glDeleteShader(fs);
	}


}

void Shader::setAttributes() {}

void Shader::enable() {
	glUseProgram(ID);
}

void Shader::disable() {
	glUseProgram(0);
}

void Shader::del() {
	glDeleteProgram(ID);
}