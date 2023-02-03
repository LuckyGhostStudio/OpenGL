#pragma once

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

#include "Light.h"

class SpotLight : public Light
{
public:
	float angleInner = 25.8f;	//内张角	25.8
	float angleOutter = 31.7f;	//外张角 31.7

	float constant;		//灯光强度衰减常数项系数
	float linear;		//灯光强度衰减一次项系数
	float quadratic;	//灯光强度衰减二次项系数

	/// <summary>
	/// 聚光灯
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="angles">旋转角度</param>
	/// <param name="color">颜色</param>
	/// <param name="intensity">光照强度</param>
	SpotLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);
};

