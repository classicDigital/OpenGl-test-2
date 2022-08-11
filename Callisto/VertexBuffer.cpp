#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, GLenum usage) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, usage);
}