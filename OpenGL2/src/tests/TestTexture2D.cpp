#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestTexture2D::TestTexture2D() 
		:m_Project(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),	//����ͶӰ
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
		float positions[] = {
			//---λ��---   -��������-
			 -50.0f,  -50.0f, 0.0f, 0.0f,	//����
			  50.0f,  -50.0f, 1.0f, 0.0f,	//����
			  50.0f,   50.0f, 1.0f, 1.0f,	//����
			 -50.0f,   50.0f, 0.0f, 1.0f	//����
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));		//���û��
		//Դalpha Ŀ��1-alpha��Դ��ɫ[ƬԪ��ɫ�������ɫ] * alpha + Ŀ����ɫ[��������ɫ] *��1-alpha��
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));	//��ϣ�Դ������ԴRGBA���ӵķ�ʽ��Ĭ��*1�� Ŀ�꣨Ĭ��*0����Ĭ��Դ����Ŀ�꡿

		m_VAO = std::make_unique<VertexArray>();
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));	//���㻺��
		VertexBufferLayout layout;		//�������Բ���
		layout.Push<float>(2);			//��Ӷ������ԣ�����λ��
		layout.Push<float>(2);			//��Ӷ������ԣ���������
		m_VAO->AddBuffer(*m_VertexBuffer, layout);	//�������ж������Բ���

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);		//����uniform���� u_Color

		m_Texture  = std::make_unique<Texture>("res/textures/C++Logo.png");	//����
		m_Shader->SetUniform1i("u_Texture", 0);			//��������uniform����Ϊ0�Ų�λ
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));	//������ɫ
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->Bind();	//��0�Ų�λ

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);	//ģ�;���ƽ��
			glm::mat4 mvp = m_Project * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);						//����u_MVP����

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);	//ģ�;���ƽ��
			glm::mat4 mvp = m_Project * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);						//����u_MVP����

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);   //������������ ��Сֵ ���ֵ
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);   //������������ ��Сֵ ���ֵ

		//��ʾ֡��
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}