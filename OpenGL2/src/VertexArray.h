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
	/// 添加顶点缓存：设置所有顶点属性布局
	/// </summary>
	/// <param name="vb">顶点缓存</param>
	/// <param name="layout">顶点缓存布局</param>
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	/// <summary>
	/// 绑定顶点数组
	/// </summary>
	void Bind() const;

	/// <summary>
	/// 解除绑定
	/// </summary>
	void Unbind() const;
};