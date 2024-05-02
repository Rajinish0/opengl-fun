#ifndef WINDOW_H
#define WINDOW_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class windowError {

public:
	std::string message;

	windowError(std::string);
	std::string what();

};


void winCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


struct Window {
	GLFWwindow* win;
	int W, H;
	Window(int width, int height, std::string name);
	bool shouldClose();
	void procedure();
};

#endif