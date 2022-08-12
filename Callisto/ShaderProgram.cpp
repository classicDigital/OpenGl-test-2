#include "ShaderProgram.h"

std::string getFile(const char* PATH) {
	std::ifstream file;
	std::stringstream buffer;
	std::string data;

	file.open(PATH);
	buffer << file.rdbuf();
	file.close();
	data = buffer.str();
	return data;
}

Shader::Shader() {}

void Shader::enable() {}

void Shader::disable() {}

void Shader::del() {}

void Shader::setAttributes() {}