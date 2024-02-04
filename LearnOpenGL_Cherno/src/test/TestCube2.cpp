#include "TestCube2.h"

namespace Test {

	TestCube2::TestCube2()
	{
		m_Shader = std::make_unique<Shader>("res/shader/Test/TextureShader.shader");
		m_Cube = std::make_unique<Blaze::Cube2>(1, 1, 1);
		m_Triangle = std::make_unique<Blaze::Triangle>();

		m_Shader->Bind();
	}

	TestCube2::~TestCube2()
	{
	}

	void TestCube2::OnUpdate(float deltaTime)
	{
	}

	void TestCube2::OnRender()
	{
		GLCall(glClearColor(0.3f, 0.2f, 0.8f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		m_Cube->Draw();
	}

	void TestCube2::OnImGuiRender()
	{
	}
}