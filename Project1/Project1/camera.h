#ifndef CAMERA_GUARD
#define CAMERA_GUARD
#include "window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Camera {

public:
	double x, y, px, py;
	glm::vec3 direction;
	glm::vec3 position;
	glm::vec3 upVec;
	float theta, phi;
	float movement = 0.001f;
	float sensitivity = 0.1f;	
	GLFWwindow* window;

	void handleMovement();
	glm::vec3 getRight();
	glm::mat4 getLookAt();

	Camera(const Window win, float theta = -90.0f, float phi = 0.0f,
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	void setDir();
	glm::mat4 getView();

};






#endif