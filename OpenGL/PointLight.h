#pragma once

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

#include "Light.h"

class PointLight : public Light
{
public:
	float constant;		//灯光强度衰减常数项系数
	float linear;		//灯光强度衰减一次项系数
	float quadratic;	//灯光强度衰减二次项系数

	/// <summary>
	/// 点光源
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="angles">旋转角度</param>
	/// <param name="color">颜色</param>
	/// <param name="intensity">光照强度</param>
	PointLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);
};

