#pragma once

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

#include "Light.h"

class DirectionalLight : public Light
{
public:
	/// <summary>
	/// ƽ�й�
	/// </summary>
	/// <param name="position">λ��</param>
	/// <param name="angles">��ת�Ƕ�</param>
	/// <param name="color">��ɫ</param>
	/// <param name="intensity">����ǿ��</param>
	DirectionalLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);
};

