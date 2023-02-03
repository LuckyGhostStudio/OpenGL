#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test
{
	/// <summary>
	/// 纹理测试
	/// </summary>
	class TestTexture2D :public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

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
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Project;	//投影矩阵
		glm::mat4 m_View;		//视图矩阵

		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
	};
}