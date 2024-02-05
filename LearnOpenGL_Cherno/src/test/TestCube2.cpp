#include "TestCube2.h"

namespace Test {

	TestCube2::TestCube2()
	{
		m_Shader = std::make_unique<Shader>("res/shader/Test/TextureShader.shader");

		/*m_Texture = std::make_unique<Texture>("res/textures/wood.png");
		m_Texture = std::make_unique<Texture>("res/textures/wood.png");*/

		m_Cube = std::make_unique<Blaze::Cube>(1.0f, 1.0f, 1.0f);
		m_Plane = std::make_unique<Blaze::Plane>(10.0f, 10.0f);

		m_Shader->Bind();
		m_Shader->SetUniform1i("uTexture", 0);
	}

	TestCube2::~TestCube2()
	{
	}

	void TestCube2::OnUpdate(float deltaTime)
	{
		m_DeltaTime = deltaTime - m_LastFrame;
		m_LastFrame = deltaTime;

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 1000.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

		glm::mat4 view = m_Camera->GetViewMatrix();
		if (m_IsOthor)
			view = glm::scale(view, glm::vec3(m_Distance));
		m_Shader->SetUniformMat4f("uView", view);
		m_Shader->SetUniformMat4f("uProjection", projection);
	}

	void TestCube2::OnRender()
	{
		GLCall(glClearColor(0.3f, 0.2f, 0.8f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glm::mat4 model = glm::mat4(1.0f);
		m_Shader->SetUniformMat4f("uModel", model);
		m_Cube->Draw();

		m_Plane->Draw();
	}

	void TestCube2::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}