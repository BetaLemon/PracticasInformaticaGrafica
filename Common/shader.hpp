#pragma once

//GLEW
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint Program;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void USE();
};

