#version 330 core

out vec4 aColor;

in vec2 Texx;

uniform sampler2D samplr;

void main() {
	aColor = texture(samplr, Texx);//vec4(0.0f, 1.0f, 0.0f, 1.0f);
}