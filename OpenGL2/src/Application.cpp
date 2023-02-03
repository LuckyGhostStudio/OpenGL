#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TextClearColor.h"
#include "tests/TestTexture2D.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "OpenGL", NULL, NULL);		//��������
	if (!window)	//����Ϊ�� ����ʧ��
	{
		glfwTerminate();	//��ֹ���ڣ�������Դ��
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);	//ǰ�󻺳����������Ϊ1 ÿһ֡����һ��

	if (glewInit() != GLEW_OK) {	//glew��ʼ��ʧ��
		std::cout << "Error!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;	//����汾��

	{
		GLCall(glEnable(GL_BLEND));		//���û��
		//Դalpha Ŀ��1-alpha��Դ��ɫ[ƬԪ��ɫ�������ɫ] * alpha + Ŀ����ɫ[��������ɫ] *��1-alpha��
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));	//��ϣ�Դ������ԴRGBA���ӵķ�ʽ��Ĭ��*1�� Ŀ�꣨Ĭ��*0����Ĭ��Դ����Ŀ�꡿

		Renderer renderer;

		ImGui::CreateContext();					//����imgui������
		ImGui_ImplGlfwGL3_Init(window, true);	//��ʼ��window
		ImGui::StyleColorsDark();				//����UI��ʽ

		test::Test* currentTest = nullptr;	//��ǰ����
		test::TestMenu* testMenu = new test::TestMenu(currentTest);	//���Բ˵�
		currentTest = testMenu;	//��ǰ���Գ�ʼΪ���Բ˵�

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");	//ע����ɫ��������
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");		//ע��2d�������

		while (!glfwWindowShouldClose(window))		//���رմ���windowʱ
		{
			GLCall(glClearColor(0, 0, 0, 1));
			renderer.Clear();

			ImGui_ImplGlfwGL3_NewFrame();	//������֡

			if (currentTest) {	//��ǰ����Ϊ��
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();

				ImGui::Begin("Test");	//����ImGui����

				//��ǰ���Բ��ǲ��Բ˵� ����������ť ����ť����ʱ
				if (currentTest != testMenu && ImGui::Button("<-")) {
					delete currentTest;		//���ٵ�ǰ����ʵ��
					currentTest = testMenu;	//���ز��Բ˵�
				}

				currentTest->OnImGuiRender();	//��ȾGUI���

				ImGui::End();	//�ر�ImGui����
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);			//����˫���壨ǰ�󻺳�����

			glfwPollEvents();	//��ȡ����
		}
		delete currentTest;
		if (currentTest != testMenu) delete testMenu;
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}