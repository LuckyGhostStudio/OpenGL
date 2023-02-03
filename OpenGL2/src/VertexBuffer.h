#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	/// <summary>
	/// ���㻺��
	/// </summary>
	/// <param name="data">��������</param>
	/// <param name="size">���ݴ�С</param>
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	/// <summary>
	/// �󶨻�����
	/// </summary>
	void Bind() const;

	/// <summary>
	/// �����
	/// </summary>
	void Unbind() const;
};