#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestTexture2D::TestTexture2D() 
		:m_Project(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),	//正交投影
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
		float positions[] = {
			//---位置---   -纹理坐标-
			 -50.0f,  -50.0f, 0.0f, 0.0f,	//左下
			  50.0f,  -50.0f, 1.0f, 0.0f,	//右下
			  50.0f,   50.0f, 1.0f, 1.0f,	//右上
			 -50.0f,   50.0f, 0.0f, 1.0f	//左上
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));		//启用混合
		//源alpha 目标1-alpha：源颜色[片元着色器输出颜色] * alpha + 目标颜色[缓冲区颜色] *（1-alpha）
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));	//混合：源（计算源RGBA因子的方式，默认*1） 目标（默认*0）【默认源覆盖目标】

		m_VAO = std::make_unique<VertexArray>();
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));	//顶点缓存
		VertexBufferLayout layout;		//顶点属性布局
		layout.Push<float>(2);			//添加顶点属性：顶点位置
		layout.Push<float>(2);			//添加顶点属性：纹理坐标
		m_VAO->AddBuffer(*m_VertexBuffer, layout);	//设置所有顶点属性布局

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);		//设置uniform变量 u_Color

		m_Texture  = std::make_unique<Texture>("res/textures/C++Logo.png");	//纹理
		m_Shader->SetUniform1i("u_Texture", 0);			//设置纹理uniform变量为0号槽位
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));	//清屏颜色
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->Bind();	//绑定0号槽位

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);	//模型矩阵：平移
			glm::mat4 mvp = m_Project * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);						//设置u_MVP变量

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);	//模型矩阵：平移
			glm::mat4 mvp = m_Project * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);						//设置u_MVP变量

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);   //滑动条：变量 最小值 最大值
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);   //滑动条：变量 最小值 最大值

		//显示帧率
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}