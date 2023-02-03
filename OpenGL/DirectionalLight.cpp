#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 color, float intensity)
{
	this->position = position;
	this->rotation = glm::radians(rotation);	//×ªÎª»¡¶È
	this->intensity = intensity;
	this->color = color * this->intensity;

	updateDirection();
}