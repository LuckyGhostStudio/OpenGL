#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 color, float intensity)
{
	this->position = position;
	this->rotation = glm::radians(rotation);	//×ªÎª»¡¶È
	this->intensity = intensity;
	this->color = color * this->intensity;

	angleInner = glm::radians(angleInner);
	angleOutter = glm::radians(angleOutter);

	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;

	updateDirection();
}