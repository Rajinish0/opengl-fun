#pragma once
#ifndef MESH_HEADER
#define MESH_HEADER

#include<iostream>
#include<vector>
#include<string>
#include <glad/glad.h>
#include "Shader.h"
#include <GLFW/glfw3.h>


struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 tCoords;
};


struct Texture {
	std::string type;
	unsigned int id;

	Texture(std::string tp, unsigned int i);
};


struct Mesh {
	std::vector<Vertex> verticies;
	std::vector<Texture> textures;
	std::vector<unsigned int> indicies;
	unsigned int VAO, VBO, EBO;

	Mesh(std::vector<Vertex> verticies, std::vector<Texture> textures, std::vector<unsigned int> indicies);
	void draw(Shader& shdr);
	void setUpMesh(); // VAO, VBO, EBO;
};


Mesh* genSphereMesh();
Mesh* genTerrainMesh(double xOffset =0.0,
					 double zOffset =0.0);


#endif // !MESH_HEADER
