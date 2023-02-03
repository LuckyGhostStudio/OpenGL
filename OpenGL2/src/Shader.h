#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

/// <summary>
/// ��ɫ��Դ����
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
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;	//uniform����-λ��ӳ���
public:
	/// <summary>
	/// ��ɫ��
	/// </summary>
	/// <param name="filepath">�ļ�·��</param>
	Shader(const std::string& filepath);
	~Shader();

	/// <summary>
	/// ����ɫ������ʹ����ɫ��
	/// </summary>
	void Bind() const;

	/// <summary>
	/// �����
	/// </summary>
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);

	void SetUniform1f(const std::string& name, float value);

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	/// <summary>
	/// ����Shader:��shader�ļ������벻ͬ��ɫ������
	/// </summary>
	/// <param name="filePath">��ɫ���ļ�·��</param>
	/// <returns>���������ɫ������</returns>
	ShaderProgramSource ParseShader(const std::string& filePath);

	/// <summary>
	/// ������ɫ��
	/// </summary>
	/// <param name="type">��ɫ������</param>
	/// <param name="source">Դ����</param>
	/// <returns>��ɫ��id</returns>
	unsigned CompileShader(unsigned int type, const std::string& source);

	/// <summary>
	/// ������ɫ��
	/// </summary>
	/// <param name="vertexShader">������ɫ��</param>
	/// <param name="fragmentShader">ƬԪ��ɫ��</param>
	/// <returns>��ɫ������idid</returns>
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	/// <summary>
	/// ����uniform����λ��
	/// </summary>
	/// <param name="name">������</param>
	/// <returns>λ��</returns>
	int GetUniformLocation(const std::string& name) const;
};