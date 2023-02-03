#pragma once

#include <vector>
#include "Renderer.h"

/// <summary>
/// ���㻺��Ԫ�أ���������
/// </summary>
struct VertexBufferElement
{
	unsigned int type;			//��������
	unsigned int count;			//���ݸ���
	unsigned char normalized;	//�Ƿ��һ��

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type) {
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
		}
		ASSERT(false);
		return 0;
	}
};

/// <summary>
/// ���㻺�沼��
/// </summary>
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;	//���㻺���б����ж�������
	unsigned int m_Stride;	//�����С
public:
	/// <summary>
	/// ���㻺�沼��
	/// </summary>
	VertexBufferLayout() : m_Stride(0){}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	/// <summary>
	/// ��Ӷ������Ե����㻺���б�
	/// </summary>
	/// <param name="count">���ݸ���</param>
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });				//��Ӷ�������Ԫ��
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);	//�ۼƼ��㶥���С
	}

	/// <summary>
	/// ��Ӷ������Ե����㻺���б�
	/// </summary>
	/// <param name="count">���ݸ���</param>
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	/// <summary>
	/// ��Ӷ������Ե����㻺���б�
	/// </summary>
	/// <param name="count">���ݸ���</param>
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	/// <summary>
	/// ���ض��������б�
	/// </summary>
	/// <returns>���������б�</returns>
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

	/// <summary>
	/// ���ض����С
	/// </summary>
	/// <returns>�����С</returns>
	inline unsigned int GetStride() const { return m_Stride; }
};