#pragma once

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

#include "Light.h"

class PointLight : public Light
{
public:
	float constant;		//�ƹ�ǿ��˥��������ϵ��
	float linear;		//�ƹ�ǿ��˥��һ����ϵ��
	float quadratic;	//�ƹ�ǿ��˥��������ϵ��

	/// <summary>
	/// ���Դ
	/// </summary>
	/// <param name="position">λ��</param>
	/// <param name="angles">��ת�Ƕ�</param>
	/// <param name="color">��ɫ</param>
	/// <param name="intensity">����ǿ��</param>
	PointLight(glm::vec3 position, glm::vec3 rotation, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);
};

