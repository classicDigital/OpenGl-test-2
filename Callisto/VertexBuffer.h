#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>

class VertexBuffer {
public:
	GLuint ID;
	
	VertexBuffer(GLuint size, void* data, GLenum usage);
	void bind();
	void unbind();
	void del();
};

#endif