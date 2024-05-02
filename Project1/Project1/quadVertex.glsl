#version 330 core

layout(location = 0) in vec2 vdata;
layout(location = 1) in vec2 tdata;

out vec2 txxt;

uniform mat4 trans;

void main() {
	//gl_Position = trans * vec4(vdata, 1.0f);
	gl_Position = trans * vec4(vdata, 0.0f, 1.0f);
	txxt = tdata;
}