#include "ShaderProgram.h"


std::string Shader::getFile(const char* PATH) {
	std::ifstream file;
	std::stringstream buffer;
	std::string data;


	file.open(PATH);
	buffer << file.rdbuf();
	data = buffer.str();
	file.close();
	return data;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	ID = glCreateProgram();
	
	std::string __vertexsrc = getFile(vertexShaderPath);
	std::string __fragmentsrc = getFile(fragmentShaderPath);

	if (__vertexsrc == "" || __fragmentsrc == "") { std::cout << "Error opening file!\n"; }

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

		std::cout << "ERROR::COMPILING::VERTEX::SHADER\n" << info <<  std::endl;

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

		std::cout << "ERROR::COMPILING::FRAGMENT::SHADER\n" << info << std::endl;
		std::cout << info << std::endl;

		glDeleteShader(fs);
	}

	glAttachShader(ID, vs);
	glAttachShader(ID, fs);
	glLinkProgram(ID);
}

void Shader::enable() {
	glUseProgram(ID);
}

void Shader::disable() {
	glUseProgram(0);
}

void Shader::del() {
	glDeleteProgram(ID);
}

void Shader::setUniformInt(const char* variableName, GLint value) {
	glUniform1i(glGetUniformLocation(ID, variableName), value);
}

void Shader::setUniformFloat(const char* variableName, GLfloat value) {
	glUniform1f(glGetUniformLocation(ID, variableName), value);
}

void Shader::setUniformBool(const char* variableName, GLboolean value) {
	glUniform1i(glGetUniformLocation(ID, variableName), value);
}

void Shader::setUniformMat2(const char* variableName, glm::mat2x2 matrix, GLboolean transpose) {
	glUniformMatrix2fv(glGetUniformLocation(ID, variableName), 1, transpose, glm::value_ptr(matrix));
}

void Shader::setUniformMat3(const char* variableName, glm::mat3x3 matrix, GLboolean transpose) {
	glUniformMatrix3fv(glGetUniformLocation(ID, variableName), 1, transpose, glm::value_ptr(matrix));
}

void Shader::setUniformMat4(const char* variableName, glm::mat4x4 matrix, GLboolean transpose) {
	glUniformMatrix4fv(glGetUniformLocation(ID, variableName), 1, transpose, glm::value_ptr(matrix));
}