//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shader.h"
#include "Camera.h"
#include "Model.h"
#include "Object.h"
#include "material.h"
#include "Light.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <map>
#include <vector>

using namespace std;
using namespace glm;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIREFRAME = false;
float rotateX = 0.0f;
float rotateY = 0.0f;
float offsetX = 0.0f;
float offsetY = 0.0f;
float offsetZ = 0.0f;
bool keys[1024];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseScroll(GLFWwindow* window, double xScroll, double yScroll);
void DoMovement(GLFWwindow* window);
void WaterLerp(float ogYPos);
GLfloat mixValue = 0.6f;

//creamos la camara
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 7.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
vec3 camDirection = glm::normalize(camPos - camTarget);
Camera *cam = new Camera(camPos, camDirection, 0.1f, 60.f);

int modelSelect;

bool dontLerp = true;
float lerpInc = 0.05f;
float goalYPos;
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

int main() {
	modelSelect = 1;
	//initGLFW
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	//comprobar que GLFW estaactivo
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "Practica final", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		cout << "Error al iniciar glew" << endl;
		glfwTerminate();
		return NULL;
	}

	//set function when callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, MouseScroll);

	//set windows and viewport
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const GLchar* vertexPath1 = "./src/SimpleVertexShader1.vertexshader";
	const GLchar* fragmentPath1 = "./src/SimpleFragmentShader1.fragmentshader";
	const GLchar* vertexPathMultiple = "./src/VertexShaderPhongTexture.vs";
	const GLchar* fragmentPathMultiple = "./src/FragmentShaderPhongTexture.fs";

	Shader DShader = Shader::Shader(vertexPath1, fragmentPath1);
	Shader P1Shader = Shader::Shader(vertexPath1, fragmentPath1);
	Shader P2Shader = Shader::Shader(vertexPath1, fragmentPath1);
	Shader S1Shader = Shader::Shader(vertexPath1, fragmentPath1);
	Shader S2Shader = Shader::Shader(vertexPath1, fragmentPath1);
	Shader *myShader1 = new Shader(vertexPathMultiple, fragmentPathMultiple);

	// Loading materials:
	Material material1("./spider/Antenna/diffuse.png", "./spider/Antenna/glossiness.png", 32);

	//bucle de dibujado

	vec3 Dposition = vec3(0, 1, 0);
	vec3 Ddir = vec3(0, 0, -1);
	vec3 Dambient = vec3(1, 1, 1);
	vec3 Ddiffuse = vec3(1, 1, 1);
	vec3 Dspecular = vec3(1, 1, 1);
	Light Dlight(Dposition, Ddir, Dambient, Ddiffuse, Dspecular, DIRECTIONAL, 0);
	Dlight.SetAtt(1.00f, 0.05f, 0.05f);

	vec3 P1position = vec3(-5, 5, 0);
	vec3 P1dir = vec3(0, 0, 0);
	vec3 P1ambient = vec3(1, 1, 1);
	vec3 P1diffuse = vec3(1, 1, 1);
	vec3 P1specular = vec3(1, 1, 1);
	Light p1light(P1position, P1dir, P1ambient, P1diffuse, P1specular, POINT, 0);
	p1light.SetAtt(1.00f, 0.05f, 0.05f);

	vec3 P2position = vec3(5, 9, 0);
	vec3 P2dir = vec3(0, 0, 0);
	vec3 P2ambient = vec3(1, 1, 1);
	vec3 P2diffuse = vec3(1, 1, 1);
	vec3 P2specular = vec3(1, 1, 1);
	Light p2light(P2position, P2dir, P2ambient, P2diffuse, P2specular, POINT, 1);
	p2light.SetAtt(1.00f, 0.05f, 0.05f);

	vec3 S1position = vec3(-2, 0, 0);
	vec3 S1dir = vec3(0, -1, 0);
	vec3 S1ambient = vec3(0, 1, 1);
	vec3 S1diffuse = vec3(0, 1, 1);
	vec3 S1specular = vec3(0, 1, 1);
	Light s1light(S1position, S1dir, S1ambient, S1diffuse, S1specular, SPOT, 0);
	s1light.SetAtt(1.00, 0.0, 0.0);
	s1light.SetAperture(20.0f, 30.0f);

	vec3 S2position = vec3(4, -2, 0);
	vec3 S2dir = vec3(1, 0, 0);
	vec3 S2ambient = vec3(1, 1, 0);
	vec3 S2diffuse = vec3(1, 1, 0);
	vec3 S2specular = vec3(1, 1, 0);
	Light s2light(S2position, S2dir, S2ambient, S2diffuse, S2specular, SPOT, 1);
	s2light.SetAtt(1.00, 0.01, 0.01);
	s2light.SetAperture(10.0f, 20.0f);

	vec3 lightScale = vec3(0.1, 0.1, 0.1);
	vec3 lightrotate = vec3(1, 1, 1);
	FigureType type = cube;

	Object dCube(lightScale, lightrotate, Dposition, type);
	Object p1Cube(lightScale, lightrotate, P1position, type);
	Object p2Cube(lightScale, lightrotate, P2position, type);
	Object s1Cube(lightScale, lightrotate, S1position, type);
	Object s2Cube(lightScale, lightrotate, S2position, type);

	FigureType Itype = cube;
	vec3 Vposition1 = vec3(1, 0, 1);
	vec3 Vscale1 = vec3(15, 15, 15);
	vec3 Vrotate1 = vec3(1, 1, 1);
	Object ourCube1(Vscale1, Vrotate1, Vposition1, FigureType::cube);

	vec3 Vposition2 = vec3(0.0f, -3.2f, 0);
	goalYPos = Vposition2.y;
	vec3 Vscale2 = vec3(30.f);
	vec3 Vrotate2 = vec3(90, 0, 0);
	Object ourCube2(Vscale2, Vrotate2, Vposition2, FigureType::window);

	// Load models
	Model modelAntenna("./spider/Antenna/antenna2.obj");

	while (!glfwWindowShouldClose(window))
	{
		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		DoMovement(window);
		mat4 view = cam->LookAt();

		glm::mat4 projection;
		GLfloat fov = cam->GetFOV();
		projection = glm::perspective(glm::radians(fov), float(screenWidth / screenHeight), 0.1f, 100.0f);

		DShader.USE();
		mat4 Dmodel;
		Dmodel = dCube.GetModelMatrix();

		glUniform3f(glGetUniformLocation(DShader.Program, "lightColor"), Dambient.x, Dambient.y, Dambient.z);
		glUniformMatrix4fv(glGetUniformLocation(DShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(DShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(DShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(Dmodel));
		dCube.Draw();

		P1Shader.USE();
		mat4 p1model;
		p1model = p1Cube.GetModelMatrix();
		glUniform3f(glGetUniformLocation(P1Shader.Program, "lightColor"), P1ambient.x, P1ambient.y, P1ambient.z);
		glUniformMatrix4fv(glGetUniformLocation(P1Shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(P1Shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(P1Shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(p1model));
		p1Cube.Draw();

		P2Shader.USE();
		mat4 p2model;
		p2model = p2Cube.GetModelMatrix();
		glUniform3f(glGetUniformLocation(P2Shader.Program, "lightColor"), P2ambient.x, P2ambient.y, P2ambient.z);
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(p2model));
		p2Cube.Draw();

		S1Shader.USE();
		mat4 s1model;
		s1model = s1Cube.GetModelMatrix();
		glUniform3f(glGetUniformLocation(P2Shader.Program, "lightColor"), S1ambient.x, S1ambient.y, S1ambient.z);
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(s1model));
		s1Cube.Draw();

		S2Shader.USE();
		mat4 s2model;
		s2model = s2Cube.GetModelMatrix();
		glUniform3f(glGetUniformLocation(P2Shader.Program, "lightColor"), S2ambient.x, S2ambient.y, S2ambient.z);
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(P2Shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(s2model));
		s2Cube.Draw();

		vec3 cameraPosition = cam->GetPos();

		myShader1->USE();
		material1.SetMaterial(myShader1);
		material1.SetShininess(myShader1);
		material1.ActivateTextures();

		Dlight.SetLight(myShader1, cameraPosition);
		p1light.SetLight(myShader1, cameraPosition);
		p2light.SetLight(myShader1, cameraPosition);
		s1light.SetLight(myShader1, cameraPosition);
		s2light.SetLight(myShader1, cameraPosition);

		GLint modelLoc1 = glGetUniformLocation(myShader1->Program, "model");
		GLint viewLoc1 = glGetUniformLocation(myShader1->Program, "view");
		GLint projectionLoc1 = glGetUniformLocation(myShader1->Program, "projection");

		glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc1, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model3;
		GLint modelLoc3 = glGetUniformLocation(myShader1->Program, "model");

		// Draw modelAntenna ?
		glm::mat4 model6;
		model6 = glm::translate(model6, glm::vec3(0.0f, 0.0f, 0.0f));
		model6 = glm::scale(model6, glm::vec3(0.2f));
		glUniformMatrix4fv(modelLoc3, 1, GL_FALSE, glm::value_ptr(model6));
		modelAntenna.Draw(*myShader1, GL_TRIANGLES);
		
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		cam->MouseMove(window, xpos, ypos);

		//intercambia el framebuffer
		glfwSwapBuffers(window);
		//comprueba que algun disparador se halla activado
		glfwPollEvents();

	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

}

void DoMovement(GLFWwindow* window) {
	if (keys[GLFW_KEY_W])
		cam->DoMovement(window, GLFW_KEY_W);
	if (keys[GLFW_KEY_S])
		cam->DoMovement(window, GLFW_KEY_S);
	if (keys[GLFW_KEY_A])
		cam->DoMovement(window, GLFW_KEY_A);
	if (keys[GLFW_KEY_D])
		cam->DoMovement(window, GLFW_KEY_D);
	if (keys[GLFW_KEY_Q])
		cam->DoMovement(window, GLFW_KEY_Q);
	if (keys[GLFW_KEY_E])
		cam->DoMovement(window, GLFW_KEY_E);
	if (keys[GLFW_KEY_3]) {
		goalYPos = -6.6;
		dontLerp = false;
	}
	if (keys[GLFW_KEY_4]) {
		goalYPos = -3.2;
		dontLerp = false;
	}
	if (keys[GLFW_KEY_5]) {
		goalYPos = 2;
		dontLerp = false;
	}
}

void MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {
	cam->MouseScroll(window, xScroll, yScroll);
}

void WaterLerp(float ogYPos) {
	if (goalYPos - (offsetY + ogYPos) < 0.05 && goalYPos - (offsetY + ogYPos) > -0.05) {
		offsetY = goalYPos - ogYPos;
		dontLerp = true;
	}
	else if (goalYPos > offsetY + ogYPos) {
		offsetY += lerpInc;
	}
	else if (goalYPos < offsetY + ogYPos) {
		offsetY -= lerpInc;
	}
}