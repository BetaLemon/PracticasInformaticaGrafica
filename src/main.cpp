//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include <shader.hpp>
#include <SOIL.h>
//GLM
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Camera.h"

using namespace std;
using namespace glm;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIREFRAME = false;
GLfloat mixValue = 0.2f;
GLfloat rotateValue = 0;
GLfloat cubeAngleX = 0.0f;
GLfloat cubeAngleY = 0.0f;
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
const GLchar* vertexPath = "./src/SimpleVertexShader.vertexshader";
const GLchar* fragmentPath = "./src/SimpleFragmentShader.fragmentshader";

GLfloat prevMouseX = WIDTH/2, prevMouseY = HEIGHT/2;
bool firstMouseMove = true;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
float Pitch;
float Yaw;
GLfloat fov = 60.0f;

Camera cam = Camera::Camera(camPos, cameraFront, 0.05f, 60.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
glm::mat4 make_LookAt(glm::vec3 camPos, glm::vec3 camTarget, glm::vec3 upVec);
void DoMovement(GLFWwindow * window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
	//initGLFW
	GLFWwindow* window;

	//comprobar que GLFW está activo
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1-B", nullptr, nullptr);
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

	// for cursor movement:
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	// for mouse scrolling:
	glfwSetScrollCallback(window, scroll_callback);

	//set windows and viewport
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	// normalizamos el mapa:
	glViewport(0, 0, screenWidth, screenHeight);
	
	// creamos el shader:
	Shader shader = Shader::Shader(vertexPath, fragmentPath);


	GLfloat VertexBufferCube[] = {	//VBO	
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vec3 CubesPositionBuffer[] = {
		vec3(0.0f ,  0.0f,  0.0f),
		vec3(2.0f ,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f , -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f , -2.0f, -2.5f),
		vec3(1.5f ,  2.0f, -2.5f),
		vec3(1.5f ,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	// Crear los VBO, VAO y EBO
	GLuint VBO;
	//GLuint EBO;
	GLuint VAO;

	//reservar memoria para el VAO, VBO y EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	//Establecer el objeto
	glBindVertexArray(VAO);
	//Declarar el VBO y el EBO - wut??

	//Enlazar el buffer con openGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferCube), VertexBufferCube, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0, // index, which attribute
		3, // number of component per vertex attribute. Each coordinate contains 3 component
		GL_FLOAT, // data type of each component
		GL_FALSE, // need to be normalized ?
		5 * sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
		(GLvoid*)0);   // offset

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		2, // index, which attribute
		2, // number of component per vertex attribute. Each coordinate contains 3 component
		GL_FLOAT, // data type of each component
		GL_FALSE, // need to be normalized ?
		5 * sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
		(GLvoid*)(3*sizeof(GLfloat)));   // offset

	glEnableVertexAttribArray(2);

	//glVertexAttribPointer(
	//	2, // index, which attribute
	//	2, // number of component per vertex attribute. Each coordinate contains 3 component
	//	GL_FLOAT, // data type of each component
	//	GL_FALSE, // need to be normalized ?
	//	8 * sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
	//	reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));   // offset

	//glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	
	// TEXTURA 1:
	// creamos la textura:
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Texture Wrapping:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Texture Filtering:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Texture Mipmap:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	// SOIL loading texture:
	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image("./src/texture.png", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
	cout << "(" << texWidth << ", " << texHeight << ")" << endl;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	// TEXTURA 2:
	// creamos la textura:
	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Texture Wrapping:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Texture Filtering:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Texture Mipmap:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// SOIL loading texture:
	unsigned char* image2 = SOIL_load_image("./src/texturejpg.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
	cout << "(" << texWidth << ", " << texHeight << ")" << endl;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image2);

	glBindTexture(GL_TEXTURE_2D, 0);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		GLfloat actualFrame = glfwGetTime();
		cam.SetDeltatime(actualFrame - lastFrame);
		lastFrame = actualFrame;
		
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CCW);

		glEnable(GL_DEPTH_TEST);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Establecer el color de fondo
		glClearColor(0, 0, 0, 1.0);

		//establecer el shader
		//glUseProgram(programID);

		//pintar el VAO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture2"), 1);
		
		glUniform1f(glGetUniformLocation(shader.Program, "mixValue"), mixValue);

		shader.USE();

		//// T5.2

		//// Prespectiva:
		glm::mat4 proj = glm::perspective(glm::radians(cam.GetFOV()), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		glm::mat4 view;
		//Ejercicio 1:
		//view = glm::lookAt(	glm::vec3(camPos.x, camPos.y, camPos.z),
		//	glm::vec3(0.0f, 0.0f, 0.0f),
		//	glm::vec3(0.0f, 1.0f, 0.0f));
		GLfloat radio = 8.0f;
		//GLfloat X = sin(glfwGetTime())*radio;
		//GLfloat Z = cos(glfwGetTime())*radio;
		/*view = glm::lookAt(glm::vec3(X, 0.0, Z),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));*/
		GLfloat cameraSpeed = 3.0f * deltaTime;
		cam.DoMovement(window);
		/*camPos.x = (sin(glfwGetTime()) * radio)+cameraSpeed;
		camPos.z = (cos(glfwGetTime()) * radio)+cameraSpeed;*/

		//view = make_LookAt(camPos, glm::vec3(0,0,0), glm::vec3(0,1,0));
		view = cam.LookAt();

		// END EJERCICIO 1
		
		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		GLint projLoc = glGetUniformLocation(shader.Program, "proj");

		/// END EJERCICIO 1

		glBindVertexArray(VAO);
		glm::mat4 model_0;
		model_0 = glm::translate(model_0, CubesPositionBuffer[0]);
		model_0 = glm::rotate(model_0, glm::radians(cubeAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
		model_0 = glm::rotate(model_0, glm::radians(cubeAngleY), glm::vec3(0.0f, 1.0f, 0.0f));

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_0));

		for (GLuint i = 1; i < 10; i++) {
			glm::mat4 model;
			model = glm::translate(model, CubesPositionBuffer[i]);
			GLfloat angle = glfwGetTime() * 100;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.25f, 0.6f));

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		}
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		////pintar con lineas
		//if (WIREFRAME) {
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//}

		////pintar con triangulos
		//else {
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//}
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		/*glDrawArrays(GL_TRIANGLES, 0, 36);*/

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	// && action == GLFW_PRESS si queremos que no lo lea para cada iteración.

	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_UP)
	{
		/*mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;*/
		cubeAngleX+=3;
	}
	if (key == GLFW_KEY_DOWN)
	{
		/*mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;*/
		cubeAngleX -= 3;
	}
	if (key == GLFW_KEY_LEFT)
	{
		/*rotateValue+=2;*/
		cubeAngleY -= 3;
	}
	if (key == GLFW_KEY_RIGHT)
	{
		/*rotateValue-=2;*/
		cubeAngleY += 3;
	}
	if (key == GLFW_KEY_1)
	{
		mixValue = 1.0f;
	}
	if (key == GLFW_KEY_2)
	{
		mixValue = 0.0f;
	}
}

glm::mat4 make_LookAt(glm::vec3 camPos, glm::vec3 camTarget, glm::vec3 upVec) {
	glm::vec3 camDir = glm::normalize(camPos - camTarget);
	glm::vec3 camRight = glm::normalize(glm::cross(upVec, camDir));
	glm::vec3 camUp = glm::cross(camDir, camRight);

	glm::mat4 posMat;
	posMat[3][0] = -camPos.x;
	posMat[3][1] = -camPos.y;
	posMat[3][2] = -camPos.z;

	/*	[ 1, 0, 0, -Px ]
		[ 0, 1, 0, -Py ]
		[ 0, 0, 1, -Pz ]
		[ 0, 0, 0,   1 ]*/

	glm::mat4 rotateMat;
	rotateMat[0][0] = camRight.x;
	rotateMat[1][0] = camRight.y;
	rotateMat[2][0] = camRight.z;
	rotateMat[0][1] = camUp.x;
	rotateMat[1][1] = camUp.y;
	rotateMat[2][1] = camUp.z;
	rotateMat[0][2] = camDir.x;
	rotateMat[1][2] = camDir.y;
	rotateMat[2][2] = camDir.z;

	/*	[ Rx, Ry, Rz, 0 ]
		[ Ux, Uy, Uz, 0 ]
		[ Dx, Dy, Dz, 0 ]
		[ 0 , 0 , 0 , 1 ]*/

	return rotateMat * posMat;
}
// T5.2 - Ejercicio 2:
void DoMovement(GLFWwindow * window ) {
	GLboolean W = glfwGetKey(window, GLFW_KEY_W);
	GLboolean A = glfwGetKey(window, GLFW_KEY_A);
	GLboolean S = glfwGetKey(window, GLFW_KEY_S);
	GLboolean D = glfwGetKey(window, GLFW_KEY_D);
	
	if (W) {
		camPos.z -= 3.0f * deltaTime;
	}
	if (A) {
		camPos.x -= 3.0f * deltaTime;
	}
	if (S) {
		camPos.z += 3.0f * deltaTime;
	}
	if (D) {
		camPos.x += 3.0f * deltaTime;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	cam.MouseMove(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.MouseScroll(window, xoffset, yoffset);
}