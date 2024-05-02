#version 330 core

in vec3 fcol;
out vec4 fragColor;


// uniform Light light;
void main() {
	fragColor = vec4(fcol, 0.5f);
	// fragColor = vec4(0.3f, 0.4f, 0.5f, 1.0f);
}