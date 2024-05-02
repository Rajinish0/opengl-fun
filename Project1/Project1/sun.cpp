#include "sun.h"
#include "funcs.h"
#include "Shader.h"

myObj::myObj(Camera cam, Shader shader)
	: camera(cam), shdr(shader), vertss{
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
}, normals{
	 0.0f, 0.0f, -1.0f,
	 0.0f, 0.0f, -1.0f,
	 0.0f, 0.0f, -1.0f,
	 0.0f, 0.0f, -1.0f,
	 0.0f, 0.0f, -1.0f,
	 0.0f, 0.0f, -1.0f,

	 0.0f, 0.0f,  1.0f,
	 0.0f, 0.0f,  1.0f,
	 0.0f, 0.0f,  1.0f,
	 0.0f, 0.0f,  1.0f,
	 0.0f, 0.0f,  1.0f,
	 0.0f, 0.0f,  1.0f,

	-1.0f, 0.0f,  0.0f,
	-1.0f, 0.0f,  0.0f,
	-1.0f, 0.0f,  0.0f,
	-1.0f, 0.0f,  0.0f,
	-1.0f, 0.0f,  0.0f,
	-1.0f, 0.0f,  0.0f,

	 1.0f, 0.0f,  0.0f,
	 1.0f, 0.0f,  0.0f,
	 1.0f, 0.0f,  0.0f,
	 1.0f, 0.0f,  0.0f,
	 1.0f, 0.0f,  0.0f,
	 1.0f, 0.0f,  0.0f,

	 0.0f,-1.0f,  0.0f,
	 0.0f,-1.0f,  0.0f,
	 0.0f,-1.0f,  0.0f,
	 0.0f,-1.0f,  0.0f,
	 0.0f,-1.0f,  0.0f,
	 0.0f,-1.0f,  0.0f,

	 0.0f, 1.0f,  0.0f,
	 0.0f, 1.0f,  0.0f,
	 0.0f, 1.0f,  0.0f,
	 0.0f, 1.0f,  0.0f,
	 0.0f, 1.0f,  0.0f,
	 0.0f, 1.0f,  0.0f,
} {

	if (!myObj::init) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &nVBO);
		myObj::init = 1;
	}

	funcs::getColors(colors, 36);
	glGenBuffers(1, &cVBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/*
	* perhaps this should have its own in built shader
	*/

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertss), vertss, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, nVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);


}


Sphere::Sphere(Camera cam, Shader shader, int points)
	:camera(cam), shdr(shader), numPoints(points) {
	verts = new float[points * points * 3];
	textarr = new float[points * points * 3];
	indicies = new unsigned int[points * points * 6];
	funcs::genSphere(verts, textarr, numPoints);
	funcs::genStrips(indicies, numPoints);

	if (!Sphere::init) {
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &VBO2);
		glGenVertexArrays(1, &VAO);
		//glGenTextures(1, &texture);
		std::string path = "D:\\images.png";
		texture = funcs::loadTexture(path);
		Sphere::init = 1;
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numPoints * numPoints * 3, verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindTexture(GL_TEXTURE_2D, texture);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numPoints * numPoints * 2, textarr, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * (numPoints) * (numPoints) * 6, indicies, GL_STATIC_DRAW);


}


Sphere::~Sphere() {
	delete[] verts;
	delete[] indicies;
	delete[] textarr;
}

void Sphere::draw(glm::mat4 proj) {
	glm::mat4 viewMat = camera.getView();
	shdr.use();;
	shdr.setM4("trans", proj * viewMat);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (numPoints) * (numPoints) * 6, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_POINTS, 0, numPoints*numPoints);

}

void mySun::draw(glm::mat4 proj, glm::mat4 t) {
	glm::mat4 viewMat = camera.getView();
	shdr.use();
	glm::mat4 t2 = glm::mat4(1.0f);
	t2 = glm::rotate(t2, glm::radians((float)glfwGetTime() * 10.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)));
	shdr.setM4("trans", proj * t * t2);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void mySun::drawScaled(glm::mat4 proj, Shader shdr2) {
	glm::mat4 viewMat = camera.getView();
	shdr2.use();
	glm::mat4 t = glm::mat4(1.0f);
	t = glm::rotate(t, glm::radians((float)glfwGetTime() * 10.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)));
	t = glm::scale(t, glm::vec3(1.1f, 1.1f, 1.1f));
	shdr2.setM4("trans", proj * viewMat * t);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void myEarth::draw(glm::mat4 proj) {
	glm::mat4 viewMat = camera.getView();
	glm::mat4 t2 = glm::mat4(1.0f);
	t2 = glm::translate(t2, glm::vec3(5.0f, 0.0f, 0.0f));
	t2 = glm::rotate(t2, glm::radians((float)glfwGetTime() * 100.0f), glm::normalize(glm::vec3(1.0f, 0.2f, 1.0f)));
	t2 = glm::scale(t2, glm::vec3(3.0f, 3.0f, 3.0f));
	shdr.use();
	glm::mat4 t = glm::mat4(1.0f);
	t = glm::rotate(t, glm::radians((float)glfwGetTime() * 20.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)));
	shdr.setVec3("cameraPos", camera.position);
	shdr.setVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
	shdr.setVec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shdr.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shdr.setM4("proj", proj);
	shdr.setM4("viewMat", viewMat);
	shdr.setM4("t", t * t2);
	// shdr.setM4("trans", proj*viewMat*t*t2);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (numPoints) * (numPoints) * 6, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, 36);
}


myTerrain::myTerrain() 
	:myMesh(genTerrainMesh()), zOffset(0.0) {}

void myTerrain::draw(Shader& shdr) {
	zOffset += 0.01;
	myMesh->draw(shdr);
	//delete myMesh;
	//myMesh = genTerrainMesh(0.0, zOffset);






	//delete myMesh;
	//myMesh = genTerrainMesh(0.0, zOffset);
}