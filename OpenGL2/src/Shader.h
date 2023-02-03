#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

/// <summary>
/// 着色器源程序
/// </summary>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;	//uniform变量-位置映射表
public:
	/// <summary>
	/// 着色器
	/// </summary>
	/// <param name="filepath">文件路径</param>
	Shader(const std::string& filepath);
	~Shader();

	/// <summary>
	/// 绑定着色器程序：使用着色器
	/// </summary>
	void Bind() const;

	/// <summary>
	/// 解除绑定
	/// </summary>
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);

	void SetUniform1f(const std::string& name, float value);

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	/// <summary>
	/// 分析Shader:读shader文件并分离不同着色器代码
	/// </summary>
	/// <param name="filePath">着色器文件路径</param>
	/// <returns>分离出的着色器程序</returns>
	ShaderProgramSource ParseShader(const std::string& filePath);

	/// <summary>
	/// 编译着色器
	/// </summary>
	/// <param name="type">着色器类型</param>
	/// <param name="source">源程序</param>
	/// <returns>着色器id</returns>
	unsigned CompileShader(unsigned int type, const std::string& source);

	/// <summary>
	/// 创建着色器
	/// </summary>
	/// <param name="vertexShader">顶点着色器</param>
	/// <param name="fragmentShader">片元着色器</param>
	/// <returns>着色器程序idid</returns>
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	/// <summary>
	/// 返回uniform变量位置
	/// </summary>
	/// <param name="name">变量名</param>
	/// <returns>位置</returns>
	int GetUniformLocation(const std::string& name) const;
};