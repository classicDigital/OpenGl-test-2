#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(GLsizeiptr size, void* data, GLenum usage) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void ElementBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::del() {
	glDeleteBuffers(1, &ID);
}
