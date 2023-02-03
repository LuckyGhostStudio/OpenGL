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
	const std::vector<VertexBufferElement>& elements = layout.GetElements();	//���ж�������
	unsigned int offset = 0;	//��������ƫ����

	//�������ж�������
	for (unsigned int i = 0; i < elements.size(); i++) {
		const VertexBufferElement& element = elements[i];	//��������

		GLCall(glEnableVertexAttribArray(i));	//����i����λ
		//���ö������Բ��� ��λ�����ݸ������������ͣ��Ƿ��һ���������С����������ƫ����
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);		//����ƫ����
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
