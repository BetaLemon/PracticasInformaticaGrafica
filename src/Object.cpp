#include "Object.h"

Object::Object() {
	//xd
}
Object::Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef) {

	if (typef == cube) {
		GLfloat VertexBufferObject[] = {
			//front
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			0.5f ,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			//back
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			//left	
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			//right
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			//down
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			//up
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f
		};
		vec3 IndexBufferObject[] = {
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

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//tex coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	else {
		GLfloat VertexBufferObject[] = {
			//front
			0.5f,  0.5f, 0.f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			0.5f, -0.5f, 0.f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			-0.5f, -0.5f, 0.f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, 0.f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, 0.f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			0.5f ,  0.5f, 0.f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		};
		vec3 IndexBufferObject[] = {
			vec3(0.0f ,  0.0f,  0.0f),
			vec3(2.0f ,  5.0f, -15.0f),
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//tex coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	Vposition = position;
	Vrotation = rotation;
	Vscale = scale;
	type = typef;
}

Object::~Object() {

}

void Object::Draw() {
	glBindVertexArray(VAO);
	if (type == cube)
		glDrawArrays(GL_TRIANGLES, 0, 36);
	else
		glDrawArrays(GL_TRIANGLES, 0, 6);

}
void Object::Move(vec3 translation) {
	Vposition = translation;
}
void Object::Rotate(vec3 rota) {
	Vrotation = rota;
}
void Object::Scale(vec3 scal) {
	Vscale = scal;
}

FigureType Object::GetType() {
	return type;
}
mat4 Object::GetModelMatrix() {
	mat4 model;
	model = translate(model, Vposition);
	model = rotate(model, radians(Vrotation.x), vec3(1, 0, 0));
	model = rotate(model, radians(Vrotation.y), vec3(0, 1, 0));

	//in case object is a tree, calculate the rotation so it look to the camera
	if (type == leaves) {
		Object::LookAtCamera(model);
		//std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
		model = rotate(model, radians(angleToRotate), glm::vec3(0, 1, 0));
	}

	model = scale(model, Vscale);

	return model;
}

vec3 Object::GetPosition() {
	return Vposition;
}

void Object::Delete() {

}

void Object::SetCameraPos(glm::vec3 p_posCam) {
	cameraPos = p_posCam;
}

void Object::LookAtCamera(glm::mat4 model) {
	float drawingFace[] = {
		0.5f,  0.5f, 0.0f,	//A
		0.5f, -0.5f, 0.0f,	//B
		-0.5f, -0.5f, 0.0f,	//C
		-0.5f,  0.5f, 0.0f,	//D
	};
	glm::vec3 normalVector = glm::vec3(0.0f, 0.0f, -1.0f);

	//				 Drawing Face
	//  D ----------------------------------- A
	//  |                                     |
	//  |                                     |
	//  |                                     |
	//  |                                     |
	//  |                                     |
	//  |                                     |
	//  |               center                |
	//  |                                     |
	//  |                                     |
	//  |                                     |
	//  |                                     |
	//  |                                     |
	//  |                                     |
	//  C ----------------------------------- B


	//CALCULATE CENTER OF FACE ON LOCAL SPACE:
	glm::vec3 center;
	glm::vec3 a = glm::vec3(drawingFace[0], drawingFace[1], drawingFace[2]);
	glm::vec3 b = glm::vec3(drawingFace[3], drawingFace[4], drawingFace[5]);
	glm::vec3 c = glm::vec3(drawingFace[6], drawingFace[7], drawingFace[8]);
	glm::vec3 d = glm::vec3(drawingFace[9], drawingFace[10], drawingFace[11]);
	glm::vec3 horizontalVector = a - d;
	glm::vec3 verticalVector = b - a;
	center = d + horizontalVector / 2.0f;
	center += verticalVector / 2.0f;

	//MOVE CENTER OF FACE TO WORLD SPACE:
	glm::vec4 centerWorldView = model * glm::vec4(center, 1.0f);
	glm::vec2 centerWolrdView2D = glm::vec2(centerWorldView.x, centerWorldView.z);

	//CALCULATED CENTER->CamPOS VECTOR:
	glm::vec2 cameraPos2D = glm::vec2(cameraPos.x, cameraPos.z);
	glm::vec2 lookingCamVector2D = cameraPos2D - centerWolrdView2D;

	//CALCULATE ANGLE TO ROTATE:
	glm::vec4 normalVectorWorldSpace = model * glm::vec4(normalVector, 1.0f);
	glm::vec2 normalVectorWorldSpace2D = glm::vec2(normalVector.x, normalVector.z);
	float dotProduct = glm::dot(normalVectorWorldSpace2D, lookingCamVector2D);
	float modulesMultiplied = glm::length(normalVectorWorldSpace2D) * glm::length(lookingCamVector2D);
	float cosinusOfAngle = dotProduct / modulesMultiplied;
	float myPi = glm::pi<float>();
	angleToRotate = glm::acos(cosinusOfAngle) * 180.0 / myPi;
	if (cameraPos.x > centerWolrdView2D.x) {
		angleToRotate *= -1;
	}
}