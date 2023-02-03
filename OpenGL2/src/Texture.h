#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;			//纹理路径
	unsigned char* m_LocalBuffer;	//纹理数据缓存
	int m_Width;	//宽
	int m_Height;	//高
	int m_BPP;		//每个像素位数
public:
	/// <summary>
	/// 纹理
	/// </summary>
	/// <param name="filepath">纹理路径</param>
	Texture(const std::string& filepath);
	~Texture();

	/// <summary>
	/// 绑定
	/// </summary>
	/// <param name="slot">绑定的纹理槽位</param>
	void Bind(unsigned int slot = 0) const;

	/// <summary>
	/// 解除绑定
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// 返回纹理宽
	/// </summary>
	/// <returns>宽</returns>
	inline int GetWidth() const { return m_Width; }

	/// <summary>
	/// 返回纹理高
	/// </summary>
	/// <returns>高</returns>
	inline int GetHeight() const { return m_Height; }
};