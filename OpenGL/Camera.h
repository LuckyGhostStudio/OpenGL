#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	glm::vec3 position;		//λ��
	glm::vec3 forward;		//����z-
	glm::vec3 right;		//�ҷ���x+
	glm::vec3 up;			//�Ϸ���y+
	glm::vec3 worldUp;		//��������ϵy+

	float pitch;	//����
	float yaw;		//ת���

	float sensitivityX = 0.01f, sensitivityY = 0.01f;	//������

	glm::vec3 speed;

	/// <summary>
	/// ���캯��
	/// </summary>
	/// <param name="position">���λ��</param>
	/// <param name="target">LookAtĿ��λ��</param>
	/// <param name="wordUp">����y+</param>
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 wordlUp);

	/// <summary>
	/// ���캯��
	/// </summary>
	/// <param name="position">���λ��</param>
	/// <param name="pitch">forward��ˮƽ��н�</param>
	/// <param name="yaw">forward��z-�н�</param>
	/// <param name="worldUp">����y+</param>
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);

	/// <summary>
	/// ������ͼ�任����View
	/// </summary>
	/// <returns></returns>
	glm::mat4 getViewMatrix();

	/// <summary>
	/// ��������ƶ�
	/// </summary>
	/// <param name="deltaX">x��������</param>
	/// <param name="deltaY">y��������</param>
	void processMouseMovement(float deltaX, float deltaY);

	/// <summary>
	/// �������λ��
	/// </summary>
	void updatePoistion();
private:
	int moveMode = 0;	//����ƶ�ģʽ 0����FPS  1�̶�

	/// <summary>
	/// �������������
	/// </summary>
	void updateVectors();
};

