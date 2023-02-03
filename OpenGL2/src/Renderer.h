#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//���� xΪfalse ��ͣ����ִ�� �������ģʽ
#define ASSERT(x) if(!(x)) __debugbreak();					

//��ÿ������x����ǰ��ֱ���ô�������ʹ����麯��
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

/// <summary>
/// ���������ÿ������֮����
/// </summary>
void GLClearError();

/// <summary>
/// ��������ÿ������֮�����
/// </summary>
/// <param name="function">������</param>
/// <param name="file">�����ļ�</param>
/// <param name="line">������</param>
/// <returns>������</returns>
bool GLLogCall(const char* function, const char* file, int line);

/// <summary>
/// ��Ⱦ��
/// </summary>
class Renderer
{
public:
	/// <summary>
	/// ���������
	/// </summary>
	void Clear() const;

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="va">��������</param>
	/// <param name="ib">��������</param>
	/// <param name="shader">��ɫ��</param>
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};