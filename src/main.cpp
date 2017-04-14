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

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIREFRAME = false;
GLfloat mixValue = 0.2f;
GLfloat angle = 0;

const GLchar* vertexPath = "./src/SimpleVertexShader.vertexshader";
const GLchar* fragmentPath = "./src/SimpleFragmentShader.fragmentshader";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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

	//set windows and viewport
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	// normalizamos el mapa:
	glViewport(0, 0, screenWidth, screenHeight);
	
	// creamos el shader:
	Shader shader = Shader::Shader(vertexPath, fragmentPath);
	
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
	
	//fondo
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//cargamos los shader
	//GLuint programID = LoadShader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	// Definir el VBO
	GLfloat VertexBufferObject[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
	};

	// Definir el EBO
	GLuint IndexBufferObject[] = {
		0, 3, 2,
		2, 1, 0
	};

	// Crear los VBO, VAO y EBO
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	//reservar memoria para el VAO, VBO y EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Establecer el objeto
	glBindVertexArray(VAO);
	//Declarar el VBO y el EBO - wut??

	//Enlazar el buffer con openGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);
	/*
	//Establecer las propiedades de los vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//liberar el buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//liberar el buffer de vertices
	glBindVertexArray(0);
	
	// Generamos la texture:
	
	

	// Aplicamos las texturas:
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);*/

	glVertexAttribPointer(
		0, // index, which attribute
		3, // number of component per vertex attribute. Each coordinate contains 3 component
		GL_FLOAT, // data type of each component
		GL_FALSE, // need to be normalized ?
		8 * sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
		nullptr);   // offset

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1, // index, which attribute
		3, // number of component per vertex attribute. Each coordinate contains 3 component
		GL_FLOAT, // data type of each component
		GL_FALSE, // need to be normalized ?
		8 * sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
		reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));   // offset

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2, // index, which attribute
		2, // number of component per vertex attribute. Each coordinate contains 3 component
		GL_FLOAT, // data type of each component
		GL_FALSE, // need to be normalized ?
		8 * sizeof(GLfloat),  // stride, 0 -> compact, OpenGL will compute it. non-zero --> number of bytes between two consecutive vertices
		reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));   // offset

	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CCW);

		glClear(GL_COLOR_BUFFER_BIT);

		//Establecer el color de fondo
		glClearColor(1.0, 1.0, 1.0, 1.0);

		//establecer el shader
		//glUseProgram(programID);

		shader.USE();

		// Ejercicio 1:
		/*glm::mat4 trans;
		trans = glm::scale(trans, glm::vec3(0.5f, -0.5f, 0));
		trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));*/
		// Se ve invertido porque estamos escalando a números negativos.

		// Ejercicio 2:
		glm::mat4 trans;
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0));
		trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
		trans = glm::rotate(trans, (GLfloat)glm::radians(angle), glm::vec3(0, 0, 1));

		GLuint transformLoc = glGetUniformLocation(shader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));	// value_ptr és per a que OpenGL entengui la matriu de GLM

		//pintar el VAO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture2"), 1);
		
		glUniform1f(glGetUniformLocation(shader.Program, "mixValue"), mixValue);
		glBindVertexArray(VAO);

		//pintar con lineas
		if (WIREFRAME) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		//pintar con triangulos
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		WIREFRAME = !WIREFRAME;
		cout << WIREFRAME;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		angle += 10;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		angle -= 10;
	}
}
