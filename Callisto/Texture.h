#ifndef TEXTURE_H
#define TEXTURE_H

#include <STB/stb_image.h>
#include <glad/glad.h>

class Texture {
private:
	int width;
	int height;
	int channels;
public:
	GLuint ID;
	Texture(const char* PATH, bool isFlipped);
	void bind();
	void unbind();
	void del();
};

#endif