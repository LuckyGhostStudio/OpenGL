#pragma once

#include <glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"

/// <summary>
/// ����
/// </summary>
struct Vertex
{
	glm::vec3 position;		//λ��
	glm::vec3 normal;		//������
	glm::vec2 texCoord;		//uv����
};

/// <summary>
/// ��ͼ
/// </summary>
struct Texture
{
	unsigned int id;	//��ͼid
	std::string type;	//��ͼ���� ��diffuse������ / specular���淴��
	std::string path;	//��ͼ·��
};

/// <summary>
/// ����
/// </summary>
class Mesh
{
public:
	std::vector<Vertex> vertices;		//����
	std::vector<unsigned int> indices;	//��������˳��
	std::vector<Texture> textures;		//��ͼ

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="vertices">������</param>
	Mesh(float vertices[]);

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="vertices">����</param>
	/// <param name="indices">��������</param>
	/// <param name="textures">��ͼ</param>
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="shader">��ɫ��</param>
	void draw(Shader* shader);

private:
	unsigned int VAO, VBO, EBO;		//�������Զ�������VBO����λ�� ���㻺��������ö������ݣ� Ԫ�ػ���������ö���������

	/// <summary>
	/// �����������ݣ���ʼ������...
	/// </summary>
	void setupMesh();
};

