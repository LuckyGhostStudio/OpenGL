#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	/// <summary>
	/// ��Ӷ��㻺�棺�������ж������Բ���
	/// </summary>
	/// <param name="vb">���㻺��</param>
	/// <param name="layout">���㻺�沼��</param>
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	/// <summary>
	/// �󶨶�������
	/// </summary>
	void Bind() const;

	/// <summary>
	/// �����
	/// </summary>
	void Unbind() const;
};