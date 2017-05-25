#pragma once
#include <GL\glew.h>
#include<glm.hpp>
#include <gtc\matrix_transform.hpp>
using namespace glm;
#include "Shader.h"

enum FigureType {
	cube = 0,
	window = 1,
	leaves = 2,
};
class Object {

public:
	Object();
	Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef);
	~Object();

	void Draw();
	void Move(vec3 translation);
	void Rotate(vec3 rota);
	void Scale(vec3 scal);
	void Delete();
	FigureType GetType();
	mat4 GetModelMatrix();
	vec3 GetPosition();
	void LookAtCamera(glm::mat4 model);
	void SetCameraPos(glm::vec3 posCam);

private:
	GLuint VBO, VAO, EBO;
	vec3 Vposition;
	vec3 Vscale;
	vec3 Vrotation;
	FigureType type;
	glm::vec3 cameraPos;
	float angleToRotate = 0.0f;
};
