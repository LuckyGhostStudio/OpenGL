#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;	//��������
public:
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="data">��������</param>
	/// <param name="size">��������</param>
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	/// <summary>
	/// �󶨻�����
	/// </summary>
	void Bind() const;

	/// <summary>
	/// �����
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// ������������
	/// </summary>
	/// <returns>��������</returns>
	inline unsigned int GetCount() const { return m_Count; }
};