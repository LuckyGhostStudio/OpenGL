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
	/// �������
	/// </summary>
	class TestTexture2D :public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

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
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::mat4 m_Project;	//ͶӰ����
		glm::mat4 m_View;		//��ͼ����

		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
	};
}