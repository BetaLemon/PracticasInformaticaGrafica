#pragma once
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction, GLfloat sensitivity, GLfloat fov) {
	cameraPos = position;
	cameraFront = direction;
	cameraUp = glm::vec3(0.0, 1.0, 0.0);
	Sensitivity = sensitivity;
	FOV = fov;
}

Camera::~Camera() {};

void Camera::DoMovement(GLFWwindow * window) {
	GLfloat cameraSpeed = 5.0f * Deltatime;

	GLboolean W = glfwGetKey(window, GLFW_KEY_W);
	GLboolean A = glfwGetKey(window, GLFW_KEY_A);
	GLboolean S = glfwGetKey(window, GLFW_KEY_S);
	GLboolean D = glfwGetKey(window, GLFW_KEY_D);
	
	if (S) {
		cameraPos += cameraFront * cameraSpeed;
	}
	if (D) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (W) {
		cameraPos -= cameraFront * cameraSpeed;
	}
	if (A) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

void Camera::MouseMove(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		LastMx = xpos;
		LastMy = ypos;
		firstMouse = false;
	}
	GLfloat offsetX = xpos - LastMx;
	GLfloat offsetY = ypos - LastMy;	// Al revés, porque van de abajo a arriba.
	LastMx = xpos;
	LastMy = ypos;

	GLfloat sensitivity = 0.06f;
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	YAW += offsetX;
	PITCH += offsetY;

	if (PITCH > 89.0f) { PITCH = 89.0f; }
	if (PITCH < -89.0f) { PITCH = -89.0f; }

	glm::vec3 front;
	front.x = cos(glm::radians(PITCH)) * cos(glm::radians(YAW));
	front.y = sin(glm::radians(PITCH));
	front.z = cos(glm::radians(PITCH)) * sin(glm::radians(YAW));
	cameraFront = glm::normalize(front);
}

void Camera::MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {
	if (FOV >= 1.0f && FOV <= 45.0f)
		FOV -= yScroll;
	if (FOV <= 1.0f)
		FOV = 1.0f;
	if (FOV >= 45.0f)
		FOV = 45.0f;
}

glm::mat4 Camera::LookAt() {
	/*lm::vec3 camDir = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 camRight = glm::normalize(glm::cross(upVec, camDir));
	glm::vec3 camUp = glm::cross(camDir, camRight);

	glm::mat4 posMat;
	posMat[3][0] = -camPos.x;
	posMat[3][1] = -camPos.y;
	posMat[3][2] = -camPos.z;*/

	/*	[ 1, 0, 0, -Px ]
	[ 0, 1, 0, -Py ]
	[ 0, 0, 1, -Pz ]
	[ 0, 0, 0,   1 ]*/

	/*glm::mat4 rotateMat;
	rotateMat[0][0] = camRight.x;
	rotateMat[1][0] = camRight.y;
	rotateMat[2][0] = camRight.z;
	rotateMat[0][1] = camUp.x;
	rotateMat[1][1] = camUp.y;
	rotateMat[2][1] = camUp.z;
	rotateMat[0][2] = camDir.x;
	rotateMat[1][2] = camDir.y;
	rotateMat[2][2] = camDir.z;*/

	/*	[ Rx, Ry, Rz, 0 ]
	[ Ux, Uy, Uz, 0 ]
	[ Dx, Dy, Dz, 0 ]
	[ 0 , 0 , 0 , 1 ]*/

	/*return rotateMat * posMat;*/

	glm::mat4 lookAtMatrix = glm::lookAt(cameraPos, cameraPos - cameraFront, cameraUp);
	return lookAtMatrix;
}

GLfloat Camera::GetFOV() {
	return FOV;
}

void Camera::SetDeltatime(GLfloat dt) {
	Deltatime = dt;
}