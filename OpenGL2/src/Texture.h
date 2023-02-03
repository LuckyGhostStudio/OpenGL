#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;			//����·��
	unsigned char* m_LocalBuffer;	//�������ݻ���
	int m_Width;	//��
	int m_Height;	//��
	int m_BPP;		//ÿ������λ��
public:
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="filepath">����·��</param>
	Texture(const std::string& filepath);
	~Texture();

	/// <summary>
	/// ��
	/// </summary>
	/// <param name="slot">�󶨵������λ</param>
	void Bind(unsigned int slot = 0) const;

	/// <summary>
	/// �����
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// ���������
	/// </summary>
	/// <returns>��</returns>
	inline int GetWidth() const { return m_Width; }

	/// <summary>
	/// ���������
	/// </summary>
	/// <returns>��</returns>
	inline int GetHeight() const { return m_Height; }
};