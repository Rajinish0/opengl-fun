#version 330 core

layout(location = 0) in vec3 vdata;
layout(location = 1) in vec3 col;
layout(location = 2) in vec3 myn;

uniform mat4 trans;

out vec3 fcol; // not averaged anymore
void main() {
	gl_Position = trans*vec4(vdata, 1.0f);
	//fcol = vec3(0.0f, 0.0f, 1.0f);
	fcol = col;
}