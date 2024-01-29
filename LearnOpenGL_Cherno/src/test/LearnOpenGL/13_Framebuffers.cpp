#include "13_Framebuffers.h"

namespace Test {
	Part4_FrameBuffer::Part4_FrameBuffer()
	{
		m_Shader = std::make_unique<Shader>("res/shader/Part4_Framebuffer.shader");
		m_ScreenShader = std::make_unique<Shader>("res/shader/Part4_FramebufferScreen.shader");

		m_Cube = std::make_unique<Cube>(*(m_Shader.get()));
		m_Plane = std::make_unique<Plane>(*(m_Shader.get()));

		m_Framebuffer = std::make_unique<Framebuffer>(1200, 800);

		m_Screen = std::make_unique<Screen>(*(m_ScreenShader.get()), *(m_Framebuffer->GetTexture()));

		//GLCall(glEnable(GL_DEPTH_TEST));
	}

	Part4_FrameBuffer::~Part4_FrameBuffer()
	{
	}

	void Part4_FrameBuffer::OnUpdate(float deltaTime)
	{
	}

	void Part4_FrameBuffer::OnRender()
	{
		m_Framebuffer->Bind();
		GLCall(glEnable(GL_DEPTH_TEST));
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

		m_Framebuffer->Unbind();
		GLCall(glDisable(GL_DEPTH_TEST));

		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f)); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_Screen->Draw();
	}

	void Part4_FrameBuffer::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}
