#include "Shader.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Renderer.h"



Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);	//������ɫ��
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));	//ɾ����ɫ������
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];			//1���� 2Ƭ����ɫ������
	ShaderType type = ShaderType::NONE;	//����

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {	//�ҵ�#shader
			if (line.find("vertex") != std::string::npos) {	//��vertex��ɫ��
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {	//��fragment��ɫ��
				type = ShaderType::FRAGMENT;
			}
		}
		else {	//��ɫ������
			ss[(int)type] << line << "\n";	//����ɫ������д��ss
		}
	}

	return { ss[0].str(),ss[1].str() };
}

/// <summary>
/// ������ɫ��
/// </summary>
/// <param name="type">��ɫ������</param>
/// <param name="source">Դ����</param>
/// <returns>��ɫ��id</returns>
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);		//������ɫ��
	const char* src = source.c_str();			//string ת char* <=> &source[0] �׵�ַ
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);						//������ɫ��

	int result;										//������
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);	//������״̬���ر�����

	if (!result) {	//����ʧ��
		int length;		//������Ϣ����
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);			//���ش�����Ϣ����
		char* message = (char*)alloca(length * sizeof(char));	//������Ϣ ��ջ�Ϸ��������ڴ�
		glGetShaderInfoLog(id, length, &length, message);		//���ش�����Ϣ

		std::cout << "Fail to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader : " << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);

		return 0;
	}

	return id;
}

/// <summary>
/// ������ɫ��
/// </summary>
/// <param name="vertexShader">������ɫ��</param>
/// <param name="fragmentShader">ƬԪ��ɫ��</param>
/// <returns>��ɫ������idid</returns>
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();	//������ɫ������
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);		//���붥����ɫ�� ����id
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);	//����ƬԪ��ɫ�� ����id

	//��ӵ�����
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);		//���ӵ�����
	glValidateProgram(program);

	//ɾ����ɫ��
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));	//ʹ����ɫ������
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));		//����uniform����
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));		//����uniform����
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));		//����uniform����
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {	//name����
		return m_UniformLocationCache[name];	//���Ҷ�Ӧlocation������
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));		//���name��location
	if (location == -1) {	//uniform������
		std::cout << "Warning: uniform '" << name << "' is not exist" << std::endl;
	}

	m_UniformLocationCache[name] = location;	//name-locationд��ӳ���

	return location;
}
