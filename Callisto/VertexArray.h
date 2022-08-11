#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>

class VertexArray {
public:
	GLuint ID;

	VertexArray();
	void bind();
	void unbind();
	void del();
};

#endif
