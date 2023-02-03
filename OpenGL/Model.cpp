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
	//加载场景 路径 三角面化 | 翻转uv的y轴（OpenGL的uv的y轴是反的）| 计算顶点的切线和副切线
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {	//场景为空 | 数据不完整 | 根节点为空
		std::cout << "Assimp Error:" << importer.GetErrorString() << std::endl;		//场景加载失败
		return;
	}

	directory = path.substr(0, path.find_last_of('\\'));	//最后一个 \ 之前的路径
	//std::cout << "模型目录：" << directory << std::endl;
	processNode(scene->mRootNode, scene);		//深度遍历处理场景结点
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	//处理当前结点的所有Mesh
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];	//当前结点的第i个Mesh
		meshes.push_back(processMesh(mesh, scene));			//将处理后的Mesh添加到meshes列表
	}

	//遍历当前结点的每个子节点
	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;		//顶点
	std::vector<unsigned int> tempIndices;	//顶点索引顺序
	std::vector<Texture> tempTextures;		//贴图

	//遍历mesh的所有顶点
	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;	//顶点
		//位置
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;
		//法线
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		//纹理坐标
		if (mesh->mTextureCoords[0]) {	//第0个vu坐标存在
			vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			vertex.texCoord = glm::vec2(0, 0);
		}
		
		tempVertices.push_back(vertex);	//处理好的顶点添加到顶点列表
	}

	//遍历mesh的所有面
	for (int i = 0; i < mesh->mNumFaces; i++) {
		//遍历第i个面的索引
		for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);		//添加到索引列表
		}
	}
	/*
	//材质
	if (mesh->mMaterialIndex >= 0) {	//Mesh材质存在
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];		//获取场景的材质
		//加载漫反射贴图
		std::vector<Texture> diffuseTextures = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		tempTextures.insert(tempTextures.end(), diffuseTextures.begin(), diffuseTextures.end());	//插入贴图列表结尾
		//加载镜面反射贴图
		std::vector<Texture> specularTextures = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		tempTextures.insert(tempTextures.end(), specularTextures.begin(), specularTextures.end());	//插入贴图列表结尾
	}*/

	return Mesh(tempVertices, tempIndices, tempTextures);
}

/// <summary>
/// 加载纹理返回id
/// </summary>
/// <param name="texPath">纹理文件路径</param>
/// <param name="dictionary">目录路径</param>
/// <param name="textureSlot">激活纹理单元号</param>
/// <returns>生成的纹理id</returns>
unsigned int loadTexture(const char* texPath, std::string directory/*, int textureSlot*/)
{
	std::string textureName = directory + "\\" + std::string(texPath);		//纹理路径
	std::cout << textureName << std::endl;
	unsigned int textureBuffer;						//纹理缓存id
	glGenTextures(1, &textureBuffer);
	//glActiveTexture(GL_TEXTURE0 + textureSlot);		//激活纹理单元0+偏移量
	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	stbi_set_flip_vertically_on_load(true);			//翻转y轴
	int width, height, nrChannel;															//图片参数：宽 高 通道数（r g b a）
	unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &nrChannel, 0);	//加载图片

	if (data) {	//加载成功
		GLenum format = GL_RGB;				//颜色格式
		if (nrChannel == 1) {
			format = GL_RED;
		}
		else if (nrChannel == 3) {
			format = GL_RGB;
		}
		else if (nrChannel == 4) {
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, (GLint)format, width, height, 0, format, GL_UNSIGNED_BYTE, data);	//生成纹理
		glGenerateMipmap(GL_TEXTURE_2D);	//产生mipmap
	}
	else {
		std::cout << "load image failed." << std::endl;
	}
	stbi_image_free(data);	//释放data数据

	return textureBuffer;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType texType, std::string typeName)
{
	std::vector<Texture> textures;

	//遍历material中所有texType类型的纹理
	for (unsigned int i = 0; i < material->GetTextureCount(texType); i++) {
		aiString texPath;								//纹理文件路径
		material->GetTexture(texType, i, &texPath);		//获取第i个texType类型的纹理路径

		Texture texture;
		texture.id = loadTexture(texPath.C_Str(), directory);	//加载纹理
		texture.path = texPath.C_Str();
		texture.type = typeName;

		textures.push_back(texture);
	}

	return textures;
}

void Model::draw(Shader* shader)
{
	//绘制所有网格
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].draw(shader);
	}
}
