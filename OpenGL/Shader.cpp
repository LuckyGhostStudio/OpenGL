#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

/// <summary>
/// Shader构造函数
/// </summary>
/// <param name="vertexPath">顶点着色器文件路径</param>
/// <param name="fragmentPath">片元着色器文件路径</param>
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexShaderFile;		//顶点着色器文件
	ifstream fragmentShaderFile;	//片元着色器文件

	stringstream vertexShaderSStream;
	stringstream fragmentShaderSStream;

	vertexShaderFile.open(vertexPath);
	fragmentShaderFile.open(fragmentPath);

	vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);		//逻辑上打开不了 | 文件损坏
	fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try{
		if (!vertexShaderFile.is_open() || !fragmentShaderFile.is_open()) {		//文件打开失败
			throw exception("open file error!");//抛出异常
		}

		//读取文件到SStream
		vertexShaderSStream << vertexShaderFile.rdbuf();
		fragmentShaderSStream << fragmentShaderFile.rdbuf();

		//SStream转为String
		vertexShaderString = vertexShaderSStream.str();
		fragmentShaderString = fragmentShaderSStream.str();

		//String转为char*
		vertexShaderSource = vertexShaderString.c_str();
		fragmentShaderSource = fragmentShaderString.c_str();

		unsigned int vertexShaderID, fragmentShaderID;

		//顶点着色器
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);				//创建
		glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);	//设置
		glCompileShader(vertexShaderID);								//编译
		checkCompileErrors(vertexShaderID, "VERTEX_SHADER");			//检查错误

		//片元着色器
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShaderID);
		checkCompileErrors(vertexShaderID, "FRAGMENT_SHADER");

		//着色器程序
		ID = glCreateProgram();					//创建
		glAttachShader(ID, vertexShaderID);		//添加vertexShader
		glAttachShader(ID, fragmentShaderID);	//添加fragmentShader
		glLinkProgram(ID);						//链接
		checkCompileErrors(ID, "PROGRAM");		//检查错误

		//删除着色器
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();	//打印异常
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setUniform(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);	//设置shader中的paramNameString uniform变量为param
}

void Shader::setUniform(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::setUniform(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);	//设置槽位slot
}

void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;		//是否编译成功
	char infoLog[512];	//日志信息

	if (type != "PROGRAM") {	//不是程序
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);	//检查着色器编译状态

		if (!success) {	//编译不成功
			glGetShaderInfoLog(ID, 512, NULL, infoLog);	//获得报错信息
			cout << "shader compile error : " << infoLog << endl;
		}
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);	//检查程序链接状态

		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "program linking error : " << infoLog << endl;
		}
	}
}