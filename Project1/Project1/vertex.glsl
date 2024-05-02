#version 330 core

layout(location = 0) in vec3 vdata;
layout(location = 1) in vec3 col;
layout(location = 2) in vec3 myn;
layout(location = 3) in vec2 textCoords;

uniform mat4 proj;
uniform mat4 viewMat;
uniform mat4 t;

uniform vec3 cameraPos;
uniform vec3 lightPos;

out vec3 fcol; // not averaged anymore
out vec3 l;
out vec3 n;
out vec3 v;
out vec2 tCord;


void main() {
	vec4 g = t * vec4(vdata, 1.0f);
	gl_Position = proj * viewMat * g;
	mat4 gprime = transpose(inverse(t));
	l = normalize(lightPos - g.xyz);
	float x = vdata.x;
	float y = vdata.y;
	float z = vdata.z;
	vec3 norm = vec3((4 * x * (pow(x * x + z * z, 0.5) - 1.5f, 0.5) / pow(x * x + z * z, 0.5)),
		(2 * y),
		(4 * z * (pow(x * x + z * z, 0.5) - 1.5f, 0.5) / pow(x * x + z * z, 0.5)));
	n = normalize((gprime * vec4(normalize(norm), 0.0f)).xyz);
	// n = normalize(vdata); // approx.
	v = normalize(cameraPos - g.xyz);
	// fcol = vec3(0.0f, 0.0f, 1.0f);
	fcol = vec3(0.8f, 0.5f, 0.2f);
	tCord = textCoords;
}