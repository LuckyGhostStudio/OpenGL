#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	/// <summary>
	/// 顶点缓存
	/// </summary>
	/// <param name="data">顶点数据</param>
	/// <param name="size">数据大小</param>
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	/// <summary>
	/// 绑定缓冲区
	/// </summary>
	void Bind() const;

	/// <summary>
	/// 解除绑定
	/// </summary>
	void Unbind() const;
};