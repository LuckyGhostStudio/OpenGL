#pragma once

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

class Light
{
public:
	glm::vec3 position;		//λ��
	glm::vec3 rotation;		//��ת�Ƕ�
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);	//���䷽�� ��ʼ����Ϊ+z
	glm::vec3 color;		//��ɫ
	float intensity;		//����ǿ��

	Light();

	/// <summary>
	/// ��Դ
	/// </summary>
	/// <param name="position">λ��</param>
	/// <param name="angles">��ת�Ƕ�</param>
	/// <param name="color">��ɫ</param>
	/// <param name="intensity">����ǿ��</param>
	//Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);

	/// <summary>
	/// ���¹��շ���
	/// </summary>
	void updateDirection();
};

