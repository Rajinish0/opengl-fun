#pragma once
#ifndef MODEL_HEADER
#define MODEL_HEADER
#include "mesh.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"

template <typename T>
void Extend(std::vector<T>* v1, unsigned int sz);



struct Model {
	Mesh* meshObj = nullptr;
	Model* child = nullptr;

	Model(std::ifstream& file, unsigned int len = 0, unsigned int len2 = 0, unsigned int len3 = 0);
	~Model();
	void draw(Shader& shdr, int k = 1);
	int length();

};


std::vector<Texture> loadTextures(std::string path);



#endif