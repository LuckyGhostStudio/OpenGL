#include "Test.h"
#include "imgui/imgui.h"

namespace test
{
	TestMenu::TestMenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer)
	{

	}
	void TestMenu::OnImGuiRender()
	{
		//遍历测试列表
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {	//创建测试按钮 test.first.c_str()测试的按钮按下
				m_CurrentTest = test.second();	//执行创建测试的函数 创建测试实例
			}
		}
	}
}