#version 330 core

layout(location = 0) in vec3 vdata;

void main() {
	gl_Position = vec4(vdata, 1.0f);
}