#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

class Shader {
private:
	//void createShader(const GLenum TYPE);
	std::string getFile(const char* PATH);
	GLint isCompiled = 0;
public:
	GLuint ID = 0;
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void enable();
	void disable();
	void del();
	void setAttributes();
};

#endif
