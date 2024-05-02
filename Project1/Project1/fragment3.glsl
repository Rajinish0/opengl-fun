#version 330 core

in vec3 fcol;
in vec3 l;
in vec3 n; //normal
in vec3 v;
in vec2 tCord;

out vec4 fragColor;




struct Light {
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};

uniform Light light;
void main() {
	vec3 r = 2 * n * dot(n, l) - l;
	vec3 c1 = light.diffuse * max(dot(l, n), 0.0f);
	vec3 c2 = light.specular * max(dot(r, v), 0.0f);
	vec3 c3 = vec3(0.3f, 0.3f, 0.3f);
	fragColor = vec4(fcol + (c1 + c2), 1.0f);
	//fragColor = c1 + c2 + c3;
	// fragColor = vec4(0.3f, 0.4f, 0.5f, 1.0f);
}