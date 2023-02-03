#include "Light.h"

Light::Light()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::radians(glm::vec3(0, 0, 0));	//תΪ����
	intensity = 1.0f;
	color = glm::vec3(1, 1, 1) * intensity;
}

void Light::updateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);	//����Ϊ+z����

	//���ƹⷽ����ת�Ƕ���ת
	direction = glm::rotateZ(direction, rotation.z);
	direction = glm::rotateX(direction, rotation.x);
	direction = glm::rotateY(direction, rotation.y);

	direction = glm::normalize(direction);
}