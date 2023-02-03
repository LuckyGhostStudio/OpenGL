#pragma once

#include <glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"

/// <summary>
/// 顶点
/// </summary>
struct Vertex
{
	glm::vec3 position;		//位置
	glm::vec3 normal;		//法向量
	glm::vec2 texCoord;		//uv坐标
};

/// <summary>
/// 贴图
/// </summary>
struct Texture
{
	unsigned int id;	//贴图id
	std::string type;	//贴图类型 ：diffuse漫反射 / specular镜面反射
	std::string path;	//贴图路径
};

/// <summary>
/// 网格
/// </summary>
class Mesh
{
public:
	std::vector<Vertex> vertices;		//顶点
	std::vector<unsigned int> indices;	//顶点索引顺序
	std::vector<Texture> textures;		//贴图

	/// <summary>
	/// 网格
	/// </summary>
	/// <param name="vertices">顶点组</param>
	Mesh(float vertices[]);

	/// <summary>
	/// 网格
	/// </summary>
	/// <param name="vertices">顶点</param>
	/// <param name="indices">顶点索引</param>
	/// <param name="textures">贴图</param>
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	/// <summary>
	/// 绘制网格
	/// </summary>
	/// <param name="shader">着色器</param>
	void draw(Shader* shader);

private:
	unsigned int VAO, VBO, EBO;		//顶点属性对象（设置VBO到栏位） 顶点缓存对象（设置顶点数据） 元素缓存对象（设置顶点索引）

	/// <summary>
	/// 设置网格数据：初始化缓冲...
	/// </summary>
	void setupMesh();
};

