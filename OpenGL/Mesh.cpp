#include "Mesh.h"
#include <string>
#include <GL/glew.h>

Mesh::Mesh(float vertices[])
{
	this->vertices.resize(36);
	memcpy(&this->vertices[0], vertices, 36 * 8 * sizeof(float));	//����vertices�����ݵ�this.vertices

	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::draw(Shader* shader)
{
	for (int i = 0; i < textures.size(); i++) {
		int slotID = 0;					//��ͼ��λ��
		std::string uniformName = "";	//��ͼuniform������

		if (textures[i].type == "texture_diffuse") {		//��������ͼ
			slotID = Shader::DIFFUSE;						//diffuse��λ
			uniformName = "material.diffuse";
		}
		else if (textures[i].type == "texture_specular") {	//���淴����ͼ
			slotID = Shader::SPECULAR;						//specular��λ
			uniformName = "material.specular";
		}
		glActiveTexture(GL_TEXTURE0 + i);				//�����λ
		glBindTexture(GL_TEXTURE_2D, textures[i].id);		//��
		shader->setUniform(uniformName.c_str(), i);	//����Uniform����
	}
	glActiveTexture(GL_TEXTURE0);										//����texture��λ0
	
	glBindVertexArray(VAO);												//��VAO
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//����������
	glBindVertexArray(0);												//���VAO
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);		//����1��VAO
	glBindVertexArray(VAO);			//��VAO����ǰContext

	glGenBuffers(1, &VBO);																			//����1��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);																//��VBO��VAO
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);	//������ ���ж����С ��һ���������ݵ�ַ
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	//λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);	//0����λ�Ķ������ԣ�ÿ����������ݵĸ���Ϊ3�������������ݵ�����float���Ƿ��һ������false��һ������ռ�е����ֽ�����λ����ʼƫ����
	glEnableVertexAttribArray(0);												//����0����λ��������

	//��������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	//��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);	//���VAO
}
