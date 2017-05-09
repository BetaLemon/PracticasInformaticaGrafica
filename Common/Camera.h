#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 direction, GLfloat sensitivity, GLfloat fov);
	~Camera();
	// Keyboard movement:
	void DoMovement(GLFWwindow * window);
	// Mouse movement:
	void MouseMove(GLFWwindow* window, double xpos, double ypos);
	// Mouse scrolling:
	void MouseScroll(GLFWwindow* window, double xScroll, double yScroll);
	// LookAt Matrix:
	glm::mat4 LookAt();
	// Get FOV value:
	GLfloat GetFOV();
	// Set Deltatime variable:
	void SetDeltatime(GLfloat dt);
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	GLfloat Deltatime;
	GLfloat Lastframe;
	GLfloat LastMx;
	GLfloat LastMy;
	GLfloat Sensitivity;
	GLboolean firstMouse;
	GLfloat PITCH;
	GLfloat YAW;
	GLfloat FOV;
};