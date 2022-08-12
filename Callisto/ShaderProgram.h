#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <sstream>
#include <fstream>
#include <string>

std::string getFile(const char* PATH);

class Shader {
public:
	GLuint ID = 0;
	Shader();
	void enable();
	void disable();
	void del();
	void setAttributes();
};

#endif
