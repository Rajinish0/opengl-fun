#version 330 core

layout(location = 0) in vec3 vdata;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tCoord;

uniform mat4 trans;
uniform vec3 camPos;
uniform vec3 lightPos;

out vec3 fcol; // not averaged anymore
out vec3 l;
out vec3 n;
out vec3 v;
out vec2 tCoords;

void main() {
	gl_Position = trans * vec4(vdata, 1.0f);
	l = normalize(lightPos - vdata);
	n = normalize(normal);
	v = normalize(camPos - vdata);
	// fcol = vec3(0.0f, 0.0f, 1.0f);
	fcol = vec3(0.3f, abs(vdata.y)/4, 0.3f);
	tCoords = tCoord;
}