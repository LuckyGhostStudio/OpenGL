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
	window = glfwCreateWindow(960, 540, "OpenGL", NULL, NULL);		//创建窗口
	if (!window)	//窗口为空 创建失败
	{
		glfwTerminate();	//终止窗口（回收资源）
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);	//前后缓冲区交换间隔为1 每一帧交换一次

	if (glewInit() != GLEW_OK) {	//glew初始化失败
		std::cout << "Error!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;	//输出版本号

	{
		GLCall(glEnable(GL_BLEND));		//启用混合
		//源alpha 目标1-alpha：源颜色[片元着色器输出颜色] * alpha + 目标颜色[缓冲区颜色] *（1-alpha）
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));	//混合：源（计算源RGBA因子的方式，默认*1） 目标（默认*0）【默认源覆盖目标】

		Renderer renderer;

		ImGui::CreateContext();					//创建imgui上下文
		ImGui_ImplGlfwGL3_Init(window, true);	//初始化window
		ImGui::StyleColorsDark();				//设置UI样式

		test::Test* currentTest = nullptr;	//当前测试
		test::TestMenu* testMenu = new test::TestMenu(currentTest);	//测试菜单
		currentTest = testMenu;	//当前测试初始为测试菜单

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");	//注册颜色清屏测试
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");		//注册2d纹理测试

		while (!glfwWindowShouldClose(window))		//不关闭窗口window时
		{
			GLCall(glClearColor(0, 0, 0, 1));
			renderer.Clear();

			ImGui_ImplGlfwGL3_NewFrame();	//开启新帧

			if (currentTest) {	//当前测试为空
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();

				ImGui::Begin("Test");	//开启ImGui窗口

				//当前测试不是测试菜单 创建按返回钮 当按钮按下时
				if (currentTest != testMenu && ImGui::Button("<-")) {
					delete currentTest;		//销毁当前测试实例
					currentTest = testMenu;	//返回测试菜单
				}

				currentTest->OnImGuiRender();	//渲染GUI组件

				ImGui::End();	//关闭ImGui窗口
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);			//交换双缓冲（前后缓冲区）

			glfwPollEvents();	//获取输入
		}
		delete currentTest;
		if (currentTest != testMenu) delete testMenu;
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}