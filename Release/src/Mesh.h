#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shader.h"
#include <GL\glew.h>
#include <gtc\matrix_transform.hpp>
#include <glm.hpp>
#include <assimp\types.h>

using namespace std;

struct Vertex {
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh {
private:
	GLuint VAO, EBO, VBO;
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vert, vector<GLuint> ind, vector<Texture> text);
	void setupMesh();
	void Draw(Shader MeshShader, GLint DrawMode);
};