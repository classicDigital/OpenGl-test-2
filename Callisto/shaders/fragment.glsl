#version 330 core

out vec4 aColor;
uniform float time;

void main() {
	aColor = vec4(0.0f, abs(sin(time)), 0.0f, 1.0f);
}