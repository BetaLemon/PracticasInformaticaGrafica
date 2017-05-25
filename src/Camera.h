#pragma once
//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;
using namespace std;

class Camera
{
private:
	vec3 cameraPos;
	vec3 cameraFront;
	vec3 cameraUp;
	GLfloat Deltatime;
	GLfloat Lastframe;
	GLfloat LastMx;
	GLfloat LastMy;
	GLfloat Sensitivity;
	GLboolean firstMouse;
	GLfloat PITCH;
	GLfloat YAW;
	GLfloat FOV;
public:
	Camera();
	~Camera();
	Camera(vec3 position, vec3 direction, GLfloat sensitivity, GLfloat fov);
	void DoMovement(GLFWwindow * window, GLint dir);
	void MouseMove(GLFWwindow* window, double xpos, double ypos);
	void MouseScroll(GLFWwindow* window, double xScroll, double yScroll);
	mat4 LookAt();
	GLfloat GetFOV();
	vec3 GetPos();
};

