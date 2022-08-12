#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
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