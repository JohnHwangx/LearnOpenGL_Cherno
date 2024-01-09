#pragma once
#include "Test.h"

#include "Renderer.h"
#include "Texture.h"

namespace Test {
	class TestDynamicGeometry :public Test 
	{
	public:
		TestDynamicGeometry();
		~TestDynamicGeometry();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		unsigned int m_QuadVA, m_QuadVB, m_QuadIB;
		std::unique_ptr<Shader> m_Shader;

		std::unique_ptr<Texture> m_Texture[2];

		glm::mat4 m_Proj, m_View;
	};
}