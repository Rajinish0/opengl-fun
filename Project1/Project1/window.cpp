#include "window.h"


windowError::windowError(std::string msg)
	:message(msg) {}

std::string windowError::what() {
	return message;
}

void winCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}



Window::Window(int width, int height, std::string name)
	:W(width), H(height) {


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	win = glfwCreateWindow(800, 600, name.c_str(), NULL, NULL);


	if (win == NULL) {
		throw windowError("Couldn't create window");
	}

	glfwMakeContextCurrent(win);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, W, H);
	glfwSetFramebufferSizeCallback(win, winCallback);

}


bool Window::shouldClose() {
	return glfwWindowShouldClose(win);
}


void Window::procedure() {
	processInput(win);
	glfwSwapBuffers(win);
	glfwPollEvents();
	glClearColor(0.8f, 0.3f, 0.3f, 0.1f);
	//glClearColor(0.0f, 0.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // so depth buffer stores the info of the pixels' distances to the viewer, that's why I need to reset it every frame, otherwise shit may or may not get drawn, depending on how close it is ofc.
}