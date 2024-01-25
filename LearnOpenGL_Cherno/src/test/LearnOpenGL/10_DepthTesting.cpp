#include "10_DepthTesting.h"
#include "imgui/imgui.h"

namespace Test {
	Part4_DepthTesting::Part4_DepthTesting()
	{
		m_Cube = std::make_unique<Cube>();
		m_Plane = std::make_unique<Plane>();

		m_Shader = std::make_unique<Shader>("res/shader/Part4_DepthTesting.shader");

		GLCall(glEnable(GL_DEPTH_TEST));
	}
	Part4_DepthTesting::~Part4_DepthTesting()
	{
	}
	void Part4_DepthTesting::OnUpdate(float deltaTime)
	{
	}
	void Part4_DepthTesting::OnRender()
	{
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glm::mat4 view = m_Camera->GetViewMatrix();
		if (m_IsOthor)
			view = glm::scale(view, glm::vec3(m_Distance));

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 1000.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_View", view);
		m_Shader->SetUniformMat4f("u_Projection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Cube->Draw(*(m_Shader.get()));

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Cube->Draw(*(m_Shader.get()));

		model = glm::mat4(1.0f);
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Plane->Draw(*(m_Shader.get()));
	}

	void Part4_DepthTesting::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}