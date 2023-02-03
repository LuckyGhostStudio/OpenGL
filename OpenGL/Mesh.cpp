#include "Mesh.h"
#include <string>
#include <GL/glew.h>

Mesh::Mesh(float vertices[])
{
	this->vertices.resize(36);
	memcpy(&this->vertices[0], vertices, 36 * 8 * sizeof(float));	//复制vertices的数据到this.vertices

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
		int slotID = 0;					//贴图槽位号
		std::string uniformName = "";	//贴图uniform变量名

		if (textures[i].type == "texture_diffuse") {		//漫反射贴图
			slotID = Shader::DIFFUSE;						//diffuse槽位
			uniformName = "material.diffuse";
		}
		else if (textures[i].type == "texture_specular") {	//镜面反射贴图
			slotID = Shader::SPECULAR;						//specular槽位
			uniformName = "material.specular";
		}
		glActiveTexture(GL_TEXTURE0 + i);				//激活槽位
		glBindTexture(GL_TEXTURE_2D, textures[i].id);		//绑定
		shader->setUniform(uniformName.c_str(), i);	//设置Uniform变量
	}
	glActiveTexture(GL_TEXTURE0);										//激活texture槽位0
	
	glBindVertexArray(VAO);												//绑定VAO
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//绘制三角形
	glBindVertexArray(0);												//解绑VAO
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);		//生成1个VAO
	glBindVertexArray(VAO);			//绑定VAO到当前Context

	glGenBuffers(1, &VBO);																			//生成1个VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);																//绑定VBO到VAO
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);	//绑定数据 所有顶点大小 第一个顶点数据地址
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);	//0号栏位的顶点属性，每个顶点的数据的个数为3，顶点描述数据的类型float，是否归一化数据false，一个顶点占有的总字节数，位置起始偏移量
	glEnableVertexAttribArray(0);												//启用0号栏位顶点属性

	//法线属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	//纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);	//解绑VAO
}
