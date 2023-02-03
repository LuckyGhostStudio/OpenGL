#pragma once
#include <string>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int ID;	//着色器程序ID

	std::string vertexShaderString;		//顶点着色器程序String
	std::string fragmentShaderString;	//片元着色器程序String
	const char* vertexShaderSource;		//顶点着色器程序char*
	const char* fragmentShaderSource;	//片元着色器程序char*

	enum TextureSlot	//纹理槽位
	{
		DIFFUSE,	//漫反射贴图 0
		SPECULAR	//镜面反射贴图 1
	};

	/// <summary>
	/// Shader构造函数
	/// </summary>
	/// <param name="vertexPath">顶点着色器文件路径</param>
	/// <param name="fragmentPath">片元着色器文件路径</param>
	Shader(const char* vertexPath, const char* fragmentPath);

	/// <summary>
	/// 使用着色器程序
	/// </summary>
	void use();

	/// <summary>
	/// 设置Shader中的Uniform变量
	/// </summary>
	/// <param name="paramNameString">Shader中的变量名</param>
	/// <param name="param">外部变量值</param>
	void setUniform(const char* paramNameString, glm::vec3 param);

	void setUniform(const char* paramNameString, float param);

	void setUniform(const char* paramNameString, int param);

private:
	/// <summary>
	/// 检查编译错误
	/// </summary>
	/// <param name="shaderID">着色器ID</param>
	/// <param name="type">类型</param>
	void checkCompileErrors(unsigned int shaderID, std::string type);
};