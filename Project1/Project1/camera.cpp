#include "camera.h"



void Camera::setDir() {
	direction = glm::normalize(glm::vec3(glm::cos(glm::radians(theta)) * glm::cos(glm::radians(phi)),
		glm::sin(glm::radians(phi)),
		glm::sin(glm::radians(theta)) * glm::cos(glm::radians(phi))));
}

Camera::Camera(const Window window, float theta, float phi,
	glm::vec3 pos,
	glm::vec3 up)
	:window(window.win), theta(theta), phi(phi), position(pos), upVec(up), px(window.W / 2), py(window.H / 2) {
	setDir();
}


glm::vec3 Camera::getRight() {
	return glm::cross(upVec, direction);
}


void Camera::handleMovement() {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += direction * movement;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= direction * movement;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += getRight() * movement;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= getRight() * movement;

	theta += (-x + px) * sensitivity;
	phi += (-y + py) * sensitivity;
	px = x;
	py = y;

	phi = (phi > 89) ? 89.0f : (phi < -89) ? -89.0f : phi;
	theta = (theta > 360) ? (theta - 360) : (theta < -360) ? theta + 360 : theta;
}



glm::mat4 Camera::getView() {
	glfwGetCursorPos(window, &x, &y);
	handleMovement();
	setDir();
	return getLookAt();
}


glm::mat4 Camera::getLookAt() {
	glm::vec3 right = getRight();
	glm::vec3 matUP = glm::cross(direction, right);

	glm::mat4 rot = glm::mat4(glm::vec4(right, 0),
		glm::vec4(matUP, 0),
		glm::vec4(-direction, 0),
		glm::vec4(0, 0, 0, 1));
	rot = glm::transpose(rot);
	glm::mat4 trans = glm::translate(glm::mat4(1.0), -position);
	return (rot * trans);


}