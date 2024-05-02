#ifndef SHADER_H
#define SHADER_H

//#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class FileError {
	std::string message;

public:
	FileError(std::string m);
	std::string what();
};


std::string readFile(std::string filePath);


class Shader {

	std::string vertexCodeS;
	std::string fragmentCodeS;

public:
	unsigned int ID;
	Shader(const std::string vertexCodeSource, const std::string fragmentCodeSouce);
	void use();
	void setU4f(std::string name, float v1, float v2, float v3, float v4);
	void setM4(std::string name, glm::mat4 trans);
	void setVec3(std::string name, glm::vec3 vec);
	int getLoc(std::string name);
	void setInt(std::string name, int i);
	void setFloat(std::string name, float val);
};
#endif