#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <string>

#include "Mesh.h"

/// <summary>
/// 模型
/// </summary>
class Model
{
public:
	/// <summary>
	/// 模型
	/// </summary>
	/// <param name="path">路径</param>
	Model(const std::string& path);

	/// <summary>
	/// 绘制模型
	/// </summary>
	/// <param name="shader">着色器</param>
	void draw(Shader* shader);

private:
	std::vector<Mesh> meshes;	//此模型包含的所有网格
	std::string directory;		//模型目录路径

	/// <summary>
	/// 加载模型
	/// </summary>
	/// <param name="path">路径</param>
	void loadModel(const std::string& path);

	/// <summary>
	/// 处理场景中的结点：深度优先遍历
	/// </summary>
	/// <param name="node">当前结点</param>
	/// <param name="scene">场景</param>
	void processNode(aiNode* node, const aiScene* scene);

	/// <summary>
	/// 处理Mesh：将读取到的aiMesh处理成自己的Mesh类型
	/// </summary>
	/// <param name="mesh">读取到的aiMesh</param>
	/// <param name="scene">场景</param>
	/// <returns>处理后的网格</returns>
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	/// <summary>
	/// 加载材质的贴图
	/// </summary>
	/// <param name="material">材质</param>
	/// <param name="texType">贴图类型</param>
	/// <param name="typeName">类型名</param>
	/// <returns>加载完成的贴图列表</returns>
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType texType, std::string typeName);
};

