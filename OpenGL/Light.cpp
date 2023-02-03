#include "Light.h"

Light::Light()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::radians(glm::vec3(0, 0, 0));	//转为弧度
	intensity = 1.0f;
	color = glm::vec3(1, 1, 1) * intensity;
}

void Light::updateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);	//重置为+z方向

	//将灯光方向按旋转角度旋转
	direction = glm::rotateZ(direction, rotation.z);
	direction = glm::rotateX(direction, rotation.x);
	direction = glm::rotateY(direction, rotation.y);

	direction = glm::normalize(direction);
}