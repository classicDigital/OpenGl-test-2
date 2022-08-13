#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

void VertexArray::setAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, int offset) {
	glVertexAttribPointer(index, size, type, normalized, stride, (void*)offset);
}

void VertexArray::bind() {
	glBindVertexArray(ID);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

void VertexArray::del() {
	glDeleteVertexArrays(1, &ID);
}