#pragma once

#include "Test.h"

namespace test
{
	/// <summary>
	/// ����������ɫ
	/// </summary>
	class TestClearColor :public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		/// <summary>
		/// ÿ֡����
		/// </summary>
		/// <param name="deltaTime">ÿ֡��ʱ����</param>
		void OnUpdate(float deltaTime) override;

		/// <summary>
		/// ��Ⱦ
		/// </summary>
		void OnRender() override;

		/// <summary>
		/// ��ȾIMGUI
		/// </summary>
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}