#pragma once

#include "Shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Material
{
public:
	Shader* shader;
	unsigned int diffuseTex;	//��������ͼid
	unsigned int specularTex;	//���淴��ͼid
	float shininess;	//�߹�ǿ��

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="shader">��ɫ��</param>
	/// <param name="diffuse">��������ͼid</param>
	/// <param name="specular">���淴����ͼid</param>
	/// <param name="shininess">�߹�ǿ��</param>
	Material(Shader* shader, unsigned int diffuse, unsigned int specular, float shininess);
};

