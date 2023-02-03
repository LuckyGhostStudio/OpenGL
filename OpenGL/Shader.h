#pragma once
#include <string>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;	//��ɫ������ID

	std::string vertexShaderString;		//������ɫ������String
	std::string fragmentShaderString;	//ƬԪ��ɫ������String
	const char* vertexShaderSource;		//������ɫ������char*
	const char* fragmentShaderSource;	//ƬԪ��ɫ������char*

	enum TextureSlot	//�����λ
	{
		DIFFUSE,	//��������ͼ 0
		SPECULAR	//���淴����ͼ 1
	};

	/// <summary>
	/// Shader���캯��
	/// </summary>
	/// <param name="vertexPath">������ɫ���ļ�·��</param>
	/// <param name="fragmentPath">ƬԪ��ɫ���ļ�·��</param>
	Shader(const char* vertexPath, const char* fragmentPath);

	/// <summary>
	/// ʹ����ɫ������
	/// </summary>
	void use();

	/// <summary>
	/// ����Shader�е�Uniform����
	/// </summary>
	/// <param name="paramNameString">Shader�еı�����</param>
	/// <param name="param">�ⲿ����ֵ</param>
	void setUniform(const char* paramNameString, glm::vec3 param);

	void setUniform(const char* paramNameString, float param);

	void setUniform(const char* paramNameString, int param);

private:
	/// <summary>
	/// ���������
	/// </summary>
	/// <param name="shaderID">��ɫ��ID</param>
	/// <param name="type">����</param>
	void checkCompileErrors(unsigned int shaderID, std::string type);
};