#include "window.h"
#include "Shader.h"
#include "funcs.h"
#include "sun.h"
#include "camera.h"
#include "model.h"

Window window{ 800, 600, "my new window" };

// float verts[] = {

// 	//verts       	// colrs
// 	0.0f, 0.5f,     1.0f, 0.0f, 0.0f,
// 	0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
//    -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
// };


float verts[] = {
	// Back face
	-0.5f, -0.5f, -0.5f, // Bottom-left
	 0.5f,  0.5f, -0.5f, // top-right
	 0.5f, -0.5f, -0.5f, // bottom-right         
	 0.5f,  0.5f, -0.5f, // top-right
	-0.5f, -0.5f, -0.5f, // bottom-left
	-0.5f,  0.5f, -0.5f, // top-left
	// Front face
	-0.5f, -0.5f,  0.5f, // bottom-left
	 0.5f, -0.5f,  0.5f, // bottom-right
	 0.5f,  0.5f,  0.5f, // top-right
	 0.5f,  0.5f,  0.5f, // top-right
	-0.5f,  0.5f,  0.5f, // top-left
	-0.5f, -0.5f,  0.5f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// Right face
	 0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 // Bottom face
	 -0.5f, -0.5f, -0.5f,
	  0.5f, -0.5f, -0.5f,
	  0.5f, -0.5f,  0.5f,
	  0.5f, -0.5f,  0.5f,
	 -0.5f, -0.5f,  0.5f,
	 -0.5f, -0.5f, -0.5f,
	 // Top face
	 -0.5f,  0.5f, -0.5f,
	  0.5f,  0.5f,  0.5f,
	  0.5f,  0.5f, -0.5f,
	  0.5f,  0.5f,  0.5f,
	 -0.5f,  0.5f, -0.5f,
	 -0.5f,  0.5f,  0.5f,
};

unsigned int indicies[] = {
	0, 1, 2, 3, 4, 5
};


float verts2[] = {
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

float verts3[] = {
   -1.0f,-1.0f,   0.0f, 0.0f,
	1.0f,-1.0f,   1.0f, 0.0f,
   -1.0f, 1.0f,   0.0f, 1.0f,
	1.0f, 1.0f,   1.0f, 1.0f,
};

unsigned int inds[]{
	0, 1, 2,
	1, 2, 3
};

// float verts[24] = {0.0f, 0.0f};
float colors[36 * 3];
// genStar(newVerts);

Shader myShdr{ "vertexLight.glsl", "fragmentLight.glsl" };
Shader myShdr2{ "vertex.glsl", "fragment.glsl" };
Shader myShdr3{ "vertex2.glsl", "fragment2.glsl" };
Shader myShdr4{ "vertexLight.glsl", "myFragment.glsl" };
Shader myShdr5{ "vertexSphere.glsl", "myFragment.glsl" };
Shader myShdr6{ "vertex2.glsl", "fragmentLight.glsl" };

Camera cam{ window };
mySun Sun{ cam, myShdr };

unsigned int fbo, VAO, VBO, EBO;


int main() {

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	unsigned int colorTexture, depthStencilTexture;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &colorTexture);
	glGenTextures(1, &depthStencilTexture);

	glBindTexture(GL_TEXTURE_2D, colorTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_INT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	glBindTexture(GL_TEXTURE_2D, depthStencilTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencilTexture, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "not complete";

	glEnable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts3), verts3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);


	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	


	//glEnable(GL_STENCIL_TEST);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 t = glm::mat4(1.0f);
	t = glm::translate(t, glm::vec3(3.0f, 0.0f, 0.0f));

	glm::mat4 t2 = glm::mat4(1.0f);
	t2 = glm::scale(t2, glm::vec3(0.4f, 0.4f, 0.4f));
	

	glm::mat4 t3 = glm::mat4(1.0f);
	t3 = glm::rotate(t3, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 t4 = glm::mat4(1.0f);
	t4 = glm::translate(t4, glm::vec3(0.0f, 0.0f, -8.0f));

	glm::mat4 t5 = glm::mat4(1.0f);
	t5 = glm::translate(t5, glm::vec3(0.0f, 0.0f, -10.0f));

	Shader myshdr7{"quadVertex.glsl", "quadFrag.glsl"};

	std::cout << std::endl;
	std::cout << GL_COLOR_BUFFER_BIT << std::endl;
	std::cout << GL_DEPTH_BUFFER_BIT;

	while (!window.shouldClose()) {
		glm::mat4 viewMat = cam.getView();
		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(0.3f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		Sun.draw(proj, viewMat*t4*t*t3);
		Sun.draw(proj, viewMat*t4* t3);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glDisable(GL_DEPTH_TEST);


		Sun.draw(proj, viewMat*t);
		Sun.draw(proj, viewMat);

		myshdr7.use();
		myshdr7.setM4("trans", proj*viewMat*t2*t4);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		window.procedure();



	}

}