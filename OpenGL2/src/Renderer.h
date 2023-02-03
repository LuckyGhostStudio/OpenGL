#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//断言 x为false 暂停程序执行 进入调试模式
#define ASSERT(x) if(!(x)) __debugbreak();					

//在每个函数x调用前后分别调用错误清除和错误检查函数
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

/// <summary>
/// 清除错误：在每个函数之调用
/// </summary>
void GLClearError();

/// <summary>
/// 检查错误：在每个函数之后调用
/// </summary>
/// <param name="function">出错函数</param>
/// <param name="file">出错文件</param>
/// <param name="line">出错行</param>
/// <returns>错误结果</returns>
bool GLLogCall(const char* function, const char* file, int line);

/// <summary>
/// 渲染器
/// </summary>
class Renderer
{
public:
	/// <summary>
	/// 清除缓冲区
	/// </summary>
	void Clear() const;

	/// <summary>
	/// 绘制
	/// </summary>
	/// <param name="va">顶点数组</param>
	/// <param name="ib">索引缓存</param>
	/// <param name="shader">着色器</param>
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};