#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <string>

#include "Mesh.h"

/// <summary>
/// ģ��
/// </summary>
class Model
{
public:
	/// <summary>
	/// ģ��
	/// </summary>
	/// <param name="path">·��</param>
	Model(const std::string& path);

	/// <summary>
	/// ����ģ��
	/// </summary>
	/// <param name="shader">��ɫ��</param>
	void draw(Shader* shader);

private:
	std::vector<Mesh> meshes;	//��ģ�Ͱ�������������
	std::string directory;		//ģ��Ŀ¼·��

	/// <summary>
	/// ����ģ��
	/// </summary>
	/// <param name="path">·��</param>
	void loadModel(const std::string& path);

	/// <summary>
	/// �������еĽ�㣺������ȱ���
	/// </summary>
	/// <param name="node">��ǰ���</param>
	/// <param name="scene">����</param>
	void processNode(aiNode* node, const aiScene* scene);

	/// <summary>
	/// ����Mesh������ȡ����aiMesh������Լ���Mesh����
	/// </summary>
	/// <param name="mesh">��ȡ����aiMesh</param>
	/// <param name="scene">����</param>
	/// <returns>����������</returns>
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	/// <summary>
	/// ���ز��ʵ���ͼ
	/// </summary>
	/// <param name="material">����</param>
	/// <param name="texType">��ͼ����</param>
	/// <param name="typeName">������</param>
	/// <returns>������ɵ���ͼ�б�</returns>
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType texType, std::string typeName);
};

