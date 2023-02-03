#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath) 
	:m_RendererID(0), m_FilePath(filepath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);	//垂直翻转图像
	m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));			//生成纹理id
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));	//绑定

	//设置纹理参数
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));		//缩小过滤 线性采样
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));		//放大过滤 线性采样
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));	//x方向循环使用纹理
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));	//y方向循环使用纹理

	//生成纹理：0层级 通道RGBA 每个通道8位 - - 0边框 提供的纹理通道 数据类型 数据缓存
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));	//取消绑定

	if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);	//释放纹理缓存
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));	//删除纹理
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));		//激活纹理槽位
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));	//绑定
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));	//取消绑定
}
