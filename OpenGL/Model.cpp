#include "Model.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model(const std::string& path)
{
	loadModel(path);
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	//���س��� ·�� �����滯 | ��תuv��y�ᣨOpenGL��uv��y���Ƿ��ģ�| ���㶥������ߺ͸�����
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {	//����Ϊ�� | ���ݲ����� | ���ڵ�Ϊ��
		std::cout << "Assimp Error:" << importer.GetErrorString() << std::endl;		//��������ʧ��
		return;
	}

	directory = path.substr(0, path.find_last_of('\\'));	//���һ�� \ ֮ǰ��·��
	//std::cout << "ģ��Ŀ¼��" << directory << std::endl;
	processNode(scene->mRootNode, scene);		//��ȱ������������
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	//����ǰ��������Mesh
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];	//��ǰ���ĵ�i��Mesh
		meshes.push_back(processMesh(mesh, scene));			//��������Mesh��ӵ�meshes�б�
	}

	//������ǰ����ÿ���ӽڵ�
	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;		//����
	std::vector<unsigned int> tempIndices;	//��������˳��
	std::vector<Texture> tempTextures;		//��ͼ

	//����mesh�����ж���
	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;	//����
		//λ��
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;
		//����
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		//��������
		if (mesh->mTextureCoords[0]) {	//��0��vu�������
			vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			vertex.texCoord = glm::vec2(0, 0);
		}
		
		tempVertices.push_back(vertex);	//����õĶ�����ӵ������б�
	}

	//����mesh��������
	for (int i = 0; i < mesh->mNumFaces; i++) {
		//������i���������
		for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);		//��ӵ������б�
		}
	}
	/*
	//����
	if (mesh->mMaterialIndex >= 0) {	//Mesh���ʴ���
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];		//��ȡ�����Ĳ���
		//������������ͼ
		std::vector<Texture> diffuseTextures = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		tempTextures.insert(tempTextures.end(), diffuseTextures.begin(), diffuseTextures.end());	//������ͼ�б��β
		//���ؾ��淴����ͼ
		std::vector<Texture> specularTextures = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		tempTextures.insert(tempTextures.end(), specularTextures.begin(), specularTextures.end());	//������ͼ�б��β
	}*/

	return Mesh(tempVertices, tempIndices, tempTextures);
}

/// <summary>
/// ����������id
/// </summary>
/// <param name="texPath">�����ļ�·��</param>
/// <param name="dictionary">Ŀ¼·��</param>
/// <param name="textureSlot">��������Ԫ��</param>
/// <returns>���ɵ�����id</returns>
unsigned int loadTexture(const char* texPath, std::string directory/*, int textureSlot*/)
{
	std::string textureName = directory + "\\" + std::string(texPath);		//����·��
	std::cout << textureName << std::endl;
	unsigned int textureBuffer;						//������id
	glGenTextures(1, &textureBuffer);
	//glActiveTexture(GL_TEXTURE0 + textureSlot);		//��������Ԫ0+ƫ����
	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	stbi_set_flip_vertically_on_load(true);			//��תy��
	int width, height, nrChannel;															//ͼƬ�������� �� ͨ������r g b a��
	unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &nrChannel, 0);	//����ͼƬ

	if (data) {	//���سɹ�
		GLenum format = GL_RGB;				//��ɫ��ʽ
		if (nrChannel == 1) {
			format = GL_RED;
		}
		else if (nrChannel == 3) {
			format = GL_RGB;
		}
		else if (nrChannel == 4) {
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, (GLint)format, width, height, 0, format, GL_UNSIGNED_BYTE, data);	//��������
		glGenerateMipmap(GL_TEXTURE_2D);	//����mipmap
	}
	else {
		std::cout << "load image failed." << std::endl;
	}
	stbi_image_free(data);	//�ͷ�data����

	return textureBuffer;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType texType, std::string typeName)
{
	std::vector<Texture> textures;

	//����material������texType���͵�����
	for (unsigned int i = 0; i < material->GetTextureCount(texType); i++) {
		aiString texPath;								//�����ļ�·��
		material->GetTexture(texType, i, &texPath);		//��ȡ��i��texType���͵�����·��

		Texture texture;
		texture.id = loadTexture(texPath.C_Str(), directory);	//��������
		texture.path = texPath.C_Str();
		texture.type = typeName;

		textures.push_back(texture);
	}

	return textures;
}

void Model::draw(Shader* shader)
{
	//������������
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].draw(shader);
	}
}
