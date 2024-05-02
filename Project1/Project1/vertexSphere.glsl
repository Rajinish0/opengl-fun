#version 330 core

layout(location = 0) in vec3 vdata;
layout(location = 1) in vec2 tC;

uniform mat4 trans2;

out vec3 fcol; // not averaged anymore
out vec2 tCoords;
void main() {
	gl_Position = trans2*vec4(vdata, 1.0f);
	// fcol = vec3(0.0f, 0.0f, 1.0f);
	fcol = vec3(0.8f, 0.8f, 1.0f);
	tCoords = tC;
}