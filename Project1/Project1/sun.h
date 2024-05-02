#ifndef SUN_GUARD
#define SUN_GUARD


#include "camera.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mesh.h"


class myObj {
private:
	float vertss[18 * 6];
	float normals[18 * 6];

public:
	unsigned int VAO, VBO, cVBO, nVBO;
	float colors[36 * 3];
	int init = 0;
	Camera camera;
	Shader shdr;

public:
	myObj(Camera cam, Shader shader);

	void draw(glm::mat4 proj);

};


class Sphere {
public:
	float* verts;
	float* textarr;
	unsigned int* indicies;
	int numPoints;


public:
	unsigned int VAO, VBO, EBO, texture, VBO2;
	int init = 0;
	Camera camera;
	Shader shdr;

	Sphere(Camera cam, Shader shader, int points = 100);
	void draw(glm::mat4 proj);
	~Sphere();
};



class mySun : public myObj {
	using myObj::myObj;
public:
	void draw(glm::mat4 proj, glm::mat4 t = glm::mat4(1));
	void drawScaled(glm::mat4 proj, Shader shdr2);
};


class myEarth : public Sphere {
	using Sphere::Sphere;

public:
	void draw(glm::mat4 proj);
};


class myTerrain {
	Mesh* myMesh;
	double zOffset;
public:
	myTerrain();
	void draw(Shader& shdr);
};
#endif