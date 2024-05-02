#include "Shader.h"

FileError::FileError(std::string m)
	:message(m) {}

std::string FileError::what() { return message; }


std::string readFile(std::string filePath)
{
	std::ifstream inpf{ filePath };
	if (!inpf)
		throw(FileError("Couldn't load " + filePath));

	std::stringstream theWholeFile;

	theWholeFile << inpf.rdbuf();
	inpf.close();
	return theWholeFile.str();
}



Shader::Shader(const std::string vertexCodeSource, const std::string fragmentCodeSouce) {

	try {

		vertexCodeS = readFile(vertexCodeSource);
		fragmentCodeS = readFile(fragmentCodeSouce);

	}

	catch (FileError& e) {
		std::cout << e.what();
	}

	const char* vertexCode = vertexCodeS.c_str();
	const char* fragmentCode = fragmentCodeS.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void Shader::use() {
	glUseProgram(ID);
}


int Shader::getLoc(std::string name) {
	return glGetUniformLocation(ID, name.c_str());
}

void Shader::setU4f(std::string name, float v1, float v2, float v3, float v4) {
	// int location = glGetUniformLocation(ID, name.c_str());
	int location = getLoc(name);
	glUniform4f(location, v1, v2, v3, v4);
}

void Shader::setInt(std::string name, int i) {
	int loc = getLoc(name);
	glUniform1i(loc, i);
}

void Shader::setM4(std::string name, glm::mat4 trans) {
	int location = getLoc(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));
}

void Shader::setVec3(std::string name, glm::vec3 vec) {
	int loc = getLoc(name);
	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setFloat(std::string name, float val) {
	int loc = getLoc(name);
	glUniform1f(loc, val);
}
