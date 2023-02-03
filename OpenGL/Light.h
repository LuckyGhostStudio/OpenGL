#pragma once

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

class Light
{
public:
	glm::vec3 position;		//位置
	glm::vec3 rotation;		//旋转角度
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);	//照射方向 初始方向为+z
	glm::vec3 color;		//颜色
	float intensity;		//光照强度

	Light();

	/// <summary>
	/// 光源
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="angles">旋转角度</param>
	/// <param name="color">颜色</param>
	/// <param name="intensity">光照强度</param>
	//Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);

	/// <summary>
	/// 更新光照方向
	/// </summary>
	void updateDirection();
};

