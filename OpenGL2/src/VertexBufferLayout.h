#pragma once

#include <vector>
#include "Renderer.h"

/// <summary>
/// 顶点缓存元素：顶点属性
/// </summary>
struct VertexBufferElement
{
	unsigned int type;			//数据类型
	unsigned int count;			//数据个数
	unsigned char normalized;	//是否归一化

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
/// 顶点缓存布局
/// </summary>
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;	//顶点缓存列表：所有顶点属性
	unsigned int m_Stride;	//顶点大小
public:
	/// <summary>
	/// 顶点缓存布局
	/// </summary>
	VertexBufferLayout() : m_Stride(0){}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	/// <summary>
	/// 添加顶点属性到顶点缓存列表
	/// </summary>
	/// <param name="count">数据个数</param>
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });				//添加顶点属性元素
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);	//累计计算顶点大小
	}

	/// <summary>
	/// 添加顶点属性到顶点缓存列表
	/// </summary>
	/// <param name="count">数据个数</param>
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	/// <summary>
	/// 添加顶点属性到顶点缓存列表
	/// </summary>
	/// <param name="count">数据个数</param>
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	/// <summary>
	/// 返回顶点属性列表
	/// </summary>
	/// <returns>顶点属性列表</returns>
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

	/// <summary>
	/// 返回顶点大小
	/// </summary>
	/// <returns>顶点大小</returns>
	inline unsigned int GetStride() const { return m_Stride; }
};