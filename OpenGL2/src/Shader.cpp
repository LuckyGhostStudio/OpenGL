#include "Shader.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Renderer.h"



Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);	//创建着色器
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));	//删除着色器程序
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];			//1顶点 2片段着色器内容
	ShaderType type = ShaderType::NONE;	//类型

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {	//找到#shader
			if (line.find("vertex") != std::string::npos) {	//是vertex着色器
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {	//是fragment着色器
				type = ShaderType::FRAGMENT;
			}
		}
		else {	//着色器内容
			ss[(int)type] << line << "\n";	//将着色器内容写入ss
		}
	}

	return { ss[0].str(),ss[1].str() };
}

/// <summary>
/// 编译着色器
/// </summary>
/// <param name="type">着色器类型</param>
/// <param name="source">源程序</param>
/// <returns>着色器id</returns>
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);		//创建着色器
	const char* src = source.c_str();			//string 转 char* <=> &source[0] 首地址
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);						//编译着色器

	int result;										//编译结果
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);	//检查编译状态返回编译结果

	if (!result) {	//编译失败
		int length;		//错误信息长度
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);			//返回错误信息长度
		char* message = (char*)alloca(length * sizeof(char));	//错误信息 在栈上分配数组内存
		glGetShaderInfoLog(id, length, &length, message);		//返回错误信息

		std::cout << "Fail to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader : " << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);

		return 0;
	}

	return id;
}

/// <summary>
/// 创建着色器
/// </summary>
/// <param name="vertexShader">顶点着色器</param>
/// <param name="fragmentShader">片元着色器</param>
/// <returns>着色器程序idid</returns>
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();	//创建着色器程序
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);		//编译顶点着色器 返回id
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);	//编译片元着色器 返回id

	//添加到程序
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);		//链接到程序
	glValidateProgram(program);

	//删除着色器
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));	//使用着色器程序
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));		//设置uniform变量
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));		//设置uniform变量
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));		//设置uniform变量
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {	//name存在
		return m_UniformLocationCache[name];	//查找对应location并返回
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));		//获得name的location
	if (location == -1) {	//uniform不存在
		std::cout << "Warning: uniform '" << name << "' is not exist" << std::endl;
	}

	m_UniformLocationCache[name] = location;	//name-location写入映射表

	return location;
}
