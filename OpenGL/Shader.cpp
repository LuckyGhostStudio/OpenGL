#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

/// <summary>
/// Shader���캯��
/// </summary>
/// <param name="vertexPath">������ɫ���ļ�·��</param>
/// <param name="fragmentPath">ƬԪ��ɫ���ļ�·��</param>
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexShaderFile;		//������ɫ���ļ�
	ifstream fragmentShaderFile;	//ƬԪ��ɫ���ļ�

	stringstream vertexShaderSStream;
	stringstream fragmentShaderSStream;

	vertexShaderFile.open(vertexPath);
	fragmentShaderFile.open(fragmentPath);

	vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);		//�߼��ϴ򿪲��� | �ļ���
	fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try{
		if (!vertexShaderFile.is_open() || !fragmentShaderFile.is_open()) {		//�ļ���ʧ��
			throw exception("open file error!");//�׳��쳣
		}

		//��ȡ�ļ���SStream
		vertexShaderSStream << vertexShaderFile.rdbuf();
		fragmentShaderSStream << fragmentShaderFile.rdbuf();

		//SStreamתΪString
		vertexShaderString = vertexShaderSStream.str();
		fragmentShaderString = fragmentShaderSStream.str();

		//StringתΪchar*
		vertexShaderSource = vertexShaderString.c_str();
		fragmentShaderSource = fragmentShaderString.c_str();

		unsigned int vertexShaderID, fragmentShaderID;

		//������ɫ��
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);				//����
		glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);	//����
		glCompileShader(vertexShaderID);								//����
		checkCompileErrors(vertexShaderID, "VERTEX_SHADER");			//������

		//ƬԪ��ɫ��
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShaderID);
		checkCompileErrors(vertexShaderID, "FRAGMENT_SHADER");

		//��ɫ������
		ID = glCreateProgram();					//����
		glAttachShader(ID, vertexShaderID);		//���vertexShader
		glAttachShader(ID, fragmentShaderID);	//���fragmentShader
		glLinkProgram(ID);						//����
		checkCompileErrors(ID, "PROGRAM");		//������

		//ɾ����ɫ��
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();	//��ӡ�쳣
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setUniform(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);	//����shader�е�paramNameString uniform����Ϊparam
}

void Shader::setUniform(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::setUniform(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);	//���ò�λslot
}

void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;		//�Ƿ����ɹ�
	char infoLog[512];	//��־��Ϣ

	if (type != "PROGRAM") {	//���ǳ���
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);	//�����ɫ������״̬

		if (!success) {	//���벻�ɹ�
			glGetShaderInfoLog(ID, 512, NULL, infoLog);	//��ñ�����Ϣ
			cout << "shader compile error : " << infoLog << endl;
		}
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);	//����������״̬

		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "program linking error : " << infoLog << endl;
		}
	}
}