#version 330 core

in vec2 txxt;
out vec4 fragColor;
uniform sampler2D tex;

float offSet = 1 / 200.0f;

void main(){
	vec2 offs[] = {
		vec2(-offSet, offSet),
		vec2(0.0f, offSet),
		vec2(offSet, offSet),
		vec2(-offSet, 0.0f),
		vec2(0.0f, 0.0f),
		vec2(offSet, 0.0f),
		vec2(-offSet, offSet),
		vec2(0.0f, offSet),
		vec2(offSet, offSet),
	};


	//casual blur, can try gaussian later
	float kernel[] = {
		0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f
	};
	//float kernel[] = {
	//1.0f, 0.0f, -1.0f,
	//1.0f, 0.0f, -1.0f,
	//1.0f, 0.0f, -1.0f
	//};

	vec3 samples[9];
	for (int i = 0; i < 9; ++i)
		samples[i] = vec3(texture(tex.st, txxt + offs[i]));

	vec3 col = vec3(0.0f);

	for (int i = 0; i < 9; ++i)
		col += kernel[i] * samples[i];

	vec4 fCol = texture(tex, txxt);
	float avg = (fCol.r + fCol.g + fCol.b) / 3.0f;
	//fragColor = vec4(vec3(1.0 - fCol), 1.0);
	//fragColor = vec4(vec3(avg), 1.0f);
	fragColor = vec4(col, 1.0f);
	// 
	//vec4(1.0f, 0.4f, 0.3f, 1.0f);
}