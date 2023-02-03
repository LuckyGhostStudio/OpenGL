#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;	//索引个数
public:
	/// <summary>
	/// 索引缓存
	/// </summary>
	/// <param name="data">索引数据</param>
	/// <param name="size">索引个数</param>
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	/// <summary>
	/// 绑定缓冲区
	/// </summary>
	void Bind() const;

	/// <summary>
	/// 解除绑定
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// 返回索引个数
	/// </summary>
	/// <returns>索引个数</returns>
	inline unsigned int GetCount() const { return m_Count; }
};