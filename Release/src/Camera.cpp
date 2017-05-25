#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

Camera::Camera(vec3 position, vec3 direction, GLfloat sensitivity, GLfloat fov) {

	cameraPos = position;
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	vec3 cameraRight = glm::normalize(glm::cross(up, direction));
	cameraUp = glm::cross(direction, cameraRight);
	//camera thing
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	

	Deltatime = 0.0f;	// Time between current frame and last frame
	Lastframe = 0.0f;  	// Time of last frame
	
	YAW = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	PITCH = 0.0f;
	FOV = fov;
	Sensitivity = sensitivity;
	LastMx = 800;
	LastMy = 600;

	firstMouse = true;
}
void Camera::DoMovement(GLFWwindow * window, GLint dir) {
	// Camera controls
	
	GLfloat cameraSpeed = 3.0f * Deltatime;
	if (dir == GLFW_KEY_W) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (dir == GLFW_KEY_S)
		cameraPos -= cameraSpeed * cameraFront;
	if (dir == GLFW_KEY_A)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (dir == GLFW_KEY_D)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (dir == GLFW_KEY_Q)
		cameraPos += cameraSpeed * cameraUp;
	if (dir == GLFW_KEY_E)
		cameraPos -= cameraSpeed * cameraUp;

}
void Camera::MouseMove(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse)
	{
		LastMx = xpos;
		LastMy = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - LastMx;
	GLfloat yoffset = LastMy - ypos;
	LastMx = xpos;
	LastMy = ypos;

	xoffset *= Sensitivity;
	yoffset *= Sensitivity;

	YAW += xoffset;
	PITCH += yoffset;

	if (PITCH > 89.0f)
		PITCH = 89.0f;
	if (PITCH < -89.0f)
		PITCH = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
	front.y = sin(glm::radians(PITCH));
	front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
	cameraFront = glm::normalize(front);
}
void Camera::MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {
	if (FOV >= 1.0f && FOV <= 180.0f)
		FOV -= yScroll;
	if (FOV <= 1.0f)
		FOV = 1.0f;
	if (FOV >= 180.0f)
		FOV = 180.0f;
}
mat4 Camera::LookAt() {
	//we calculate the deltatime here for no reason lol
	GLfloat currentFrame = glfwGetTime();
	Deltatime = currentFrame - Lastframe;
	Lastframe = currentFrame;
	mat4 view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	
	vec3 up = vec3(0, 1, 0);
	vec3 cameraDirection = vec3(normalize((cameraFront + cameraPos) - cameraPos));
	vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	/*
	vec3 cameraDirection = vec3(normalize((cameraFront + cameraPos) - cameraPos));
	vec3 cameraRight = normalize(cross(up, cameraDirection));
	vec3 cammUp = cross(cameraDirection, cameraRight);
	vec4 row1 = vec4(cameraRight, 0);
	vec4 row2 = vec4(cammUp, 0);
	vec4 row3 = vec4(cameraDirection, 0);
	vec4 row4 = vec4(0, 0, 0, 1);
	vec4 row5 = vec4(1, 0, 0, -cameraPos.x);
	vec4 row6 = vec4(0, 1, 0, -cameraPos.y);
	vec4 row7 = vec4(0, 0, 1, -cameraPos.z);
	vec4 row8 = vec4(0, 0, 0, 1);
	mat4 manualView1;
	manualView1[0] = row1;
	manualView1[1] = row2;
	manualView1[2] = row3;
	manualView1[3] = row4;

	mat4 manualView2;
	manualView2[0] = row5;
	manualView2[1] = row6;
	manualView2[2] = row7;
	manualView2[3] = row8;
	mat4 lookAt = manualView2 * manualView1;
	*/
	return view;
}
GLfloat Camera::GetFOV() {
	return FOV;
}
vec3 Camera::GetPos() {
	return cameraPos;
}