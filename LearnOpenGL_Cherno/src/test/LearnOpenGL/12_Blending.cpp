#include "12_Blending.h"

namespace Test {

	Part4_Blending::Part4_Blending()
	{
		m_Shader = std::make_unique<Shader>("res/shader/Part4_Blending.shader");

		m_Cube = std::make_unique<Cube>(*(m_Shader.get()));
		m_Plane = std::make_unique<Plane>(*(m_Shader.get()));
		m_Transparent = std::make_unique<Transparent>(*(m_Shader.get()));

		GLCall(glEnable(GL_DEPTH_TEST));
	}

	Part4_Blending::~Part4_Blending()
	{
	}

	void Part4_Blending::OnUpdate(float deltaTime)
	{
	}

	void Part4_Blending::OnRender()
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
		m_Cube->SetTransform(model);
		m_Cube->Draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		m_Cube->SetTransform(model);
		m_Cube->Draw();

		model = glm::mat4(1.0f);
		m_Plane->SetTransform(model);
		m_Plane->Draw();

		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, vegetation[i]);
			m_Transparent->SetTransform(model);
			m_Transparent->Draw();
		}
	}

	void Part4_Blending::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}