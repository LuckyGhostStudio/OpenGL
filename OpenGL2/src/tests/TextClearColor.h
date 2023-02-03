#pragma once

#include "Test.h"

namespace test
{
	/// <summary>
	/// 测试清屏颜色
	/// </summary>
	class TestClearColor :public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		/// <summary>
		/// 每帧调用
		/// </summary>
		/// <param name="deltaTime">每帧的时间间隔</param>
		void OnUpdate(float deltaTime) override;

		/// <summary>
		/// 渲染
		/// </summary>
		void OnRender() override;

		/// <summary>
		/// 渲染IMGUI
		/// </summary>
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}