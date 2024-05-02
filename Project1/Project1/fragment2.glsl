#version 330 core

in vec3 fcol;
in vec3 l;
in vec3 n; //normal
in vec3 v;
in vec2 tCoords;

out vec4 fragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;


struct Light {
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};

void main() {
	vec3 r = 2 * n * dot(n, l) - l;
	//vec4 c1 = vec4(vec3(0.3, 0.2, 0.0) * max(dot(l, n), 0.0f), 1.0f);
	vec4 c1 = texture(texture_diffuse1, tCoords) * max(dot(l, n), 0.0f);
	vec4 c2 = texture(texture_specular1, tCoords) * max(dot(r, v), 0.0f);
	//vec4 c2 = vec4(vec3(0.5, 0.5, 0.5) * max(dot(r, v), 0.0f), 1.0f);
	vec4 c3 = texture(texture_diffuse1, tCoords)*vec4(0.1f, 0.1f, 0.1f, 0.0f);
	fragColor = c1 + c2 + c3;
	//fragColor = texture(texture_diffuse1, tCoords);dsasdsdsa
	//fragColor = fcol;
	//fragColor = c1 + c2 + c3;
	//fragColor = vec4(0.3f, 0.4f, 0.5f, 1.0f);
}