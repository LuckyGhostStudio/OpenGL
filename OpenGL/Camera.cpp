#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	this->position = position;
	this->worldUp = worldUp;
	this->forward = glm::normalize(target - position);						//相机指向目标 归一化
	this->right = glm::normalize(glm::cross(this->forward, this->worldUp));	//f x up = r
	this->up = glm::normalize(glm::cross(this->right, this->forward));		//up = r x f
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp)
{
	this->pitch = glm::radians(pitch);
	this->yaw = glm::radians(yaw);

	this->position = position;
	this->worldUp = worldUp;
	this->forward.x = glm::cos(this->pitch) * glm::sin(this->yaw);
	this->forward.y = glm::sin(this->pitch);
	this->forward.z = glm::cos(this->pitch) * glm::cos(this->yaw);
	this->right = glm::normalize(glm::cross(this->forward, this->worldUp));	//f x up = r
	this->up = glm::normalize(glm::cross(this->right, this->forward));		//up = r x f
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + forward, worldUp);	//相机位置 朝向 世界y+
}

void Camera::processMouseMovement(float deltaX, float deltaY)
{
	this->pitch -= deltaY * sensitivityX;
	this->yaw -= deltaX * sensitivityY;
	updateVectors();
}

void Camera::updateVectors()
{
	this->forward.x = glm::cos(this->pitch) * glm::sin(this->yaw);
	this->forward.y = glm::sin(this->pitch);
	this->forward.z = glm::cos(this->pitch) * glm::cos(this->yaw);
	this->right = glm::normalize(glm::cross(this->forward, this->worldUp));	
	this->up = glm::normalize(glm::cross(this->right, this->forward));		
}

void Camera::updatePoistion()
{
	position += (right * speed.x + up * speed.y + forward * speed.z) * 0.005f;
}
