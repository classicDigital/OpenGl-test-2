#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLsizeiptr size, void* data, GLenum usage) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::del() {
	glDeleteBuffers(1, &ID);
}