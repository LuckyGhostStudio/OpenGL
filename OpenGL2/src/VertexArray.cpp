#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement>& elements = layout.GetElements();	//所有顶点属性
	unsigned int offset = 0;	//顶点属性偏移量

	//遍历所有顶点属性
	for (unsigned int i = 0; i < elements.size(); i++) {
		const VertexBufferElement& element = elements[i];	//顶点属性

		GLCall(glEnableVertexAttribArray(i));	//启用i号栏位
		//设置顶点属性布局 栏位，数据个数，数据类型，是否归一化，顶点大小，顶点属性偏移量
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);		//计算偏移量
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
