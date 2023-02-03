#include "Test.h"
#include "imgui/imgui.h"

namespace test
{
	TestMenu::TestMenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer)
	{

	}
	void TestMenu::OnImGuiRender()
	{
		//���������б�
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {	//�������԰�ť test.first.c_str()���Եİ�ť����
				m_CurrentTest = test.second();	//ִ�д������Եĺ��� ��������ʵ��
			}
		}
	}
}