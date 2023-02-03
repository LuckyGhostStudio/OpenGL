#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace test
{
	/// <summary>
	/// 测试类：所有测试类的基类
	/// </summary>
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		/// <summary>
		/// 每帧调用
		/// </summary>
		/// <param name="deltaTime">每帧的时间间隔</param>
		virtual void OnUpdate(float deltaTime) {}

		/// <summary>
		/// 渲染
		/// </summary>
		virtual void OnRender() {}

		/// <summary>
		/// 渲染GUI
		/// </summary>
		virtual void OnImGuiRender() {}
	};

	/// <summary>
	/// 测试菜单
	/// </summary>
	class TestMenu :public Test
	{
	private:
		Test*& m_CurrentTest;	//当前测试实例指针的引用
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;	//测试列表：测试名称-可返回测试实例指针的函数（测试按钮监听函数） 对
	public:
		/// <summary>
		/// 测试菜单
		/// </summary>
		/// <param name="currentTestPointer">指向当前测试实例的指针</param>
		TestMenu(Test*& currentTestPointer);

		/// <summary>
		/// 渲染GUI
		/// </summary>
		void OnImGuiRender() override;

		/// <summary>
		/// 注册测试：创建测试实例
		/// </summary>
		/// <typeparam name="T">测试类型</typeparam>
		/// <param name="name">测试名</param>
		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { Test* t = new T(); return t; }));;	//创建测试实例 添加到测试列表
		}
	};
}