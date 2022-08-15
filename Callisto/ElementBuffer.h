#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

#include <glad/glad.h>

class ElementBuffer {
public:
	GLuint ID;
	ElementBuffer(GLsizeiptr size, void* data, GLenum usage);
	void bind();
	void unbind();
	void del();
};

#endif