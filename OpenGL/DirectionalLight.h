#pragma once

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

#include "Light.h"

class DirectionalLight : public Light
{
public:
	/// <summary>
	/// 平行光
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="angles">旋转角度</param>
	/// <param name="color">颜色</param>
	/// <param name="intensity">光照强度</param>
	DirectionalLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);
};

