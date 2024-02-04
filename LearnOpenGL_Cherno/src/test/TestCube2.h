#pragma once
#include "Test.h"
#include "Blaze/Cube2.h"
#include "Blaze/Triangle.h"

namespace Test {
	class TestCube2 :public Test
	{
	public:
		TestCube2();
		~TestCube2();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Blaze::Cube2> m_Cube;
		std::unique_ptr<Blaze::Triangle> m_Triangle;
		//std::unique_ptr<GLStaticMesh> m_CubeVAO;
		std::unique_ptr<Blaze::GLStaticMesh> m_TriangleVAO;
	};
}