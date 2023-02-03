#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace test
{
	/// <summary>
	/// �����ࣺ���в�����Ļ���
	/// </summary>
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		/// <summary>
		/// ÿ֡����
		/// </summary>
		/// <param name="deltaTime">ÿ֡��ʱ����</param>
		virtual void OnUpdate(float deltaTime) {}

		/// <summary>
		/// ��Ⱦ
		/// </summary>
		virtual void OnRender() {}

		/// <summary>
		/// ��ȾGUI
		/// </summary>
		virtual void OnImGuiRender() {}
	};

	/// <summary>
	/// ���Բ˵�
	/// </summary>
	class TestMenu :public Test
	{
	private:
		Test*& m_CurrentTest;	//��ǰ����ʵ��ָ�������
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;	//�����б���������-�ɷ��ز���ʵ��ָ��ĺ��������԰�ť���������� ��
	public:
		/// <summary>
		/// ���Բ˵�
		/// </summary>
		/// <param name="currentTestPointer">ָ��ǰ����ʵ����ָ��</param>
		TestMenu(Test*& currentTestPointer);

		/// <summary>
		/// ��ȾGUI
		/// </summary>
		void OnImGuiRender() override;

		/// <summary>
		/// ע����ԣ���������ʵ��
		/// </summary>
		/// <typeparam name="T">��������</typeparam>
		/// <param name="name">������</param>
		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { Test* t = new T(); return t; }));;	//��������ʵ�� ��ӵ������б�
		}
	};
}