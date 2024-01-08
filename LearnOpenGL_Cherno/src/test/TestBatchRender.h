#pragma once
#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

namespace Test {

	class TestBatchRender :public Test
	{
	public:
		TestBatchRender();
		~TestBatchRender();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBUffer;
		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_Proj, m_View;
	};
}