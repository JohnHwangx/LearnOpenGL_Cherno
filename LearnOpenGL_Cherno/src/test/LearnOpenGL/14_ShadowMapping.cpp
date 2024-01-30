#include "14_ShadowMapping.h"

namespace Test {

	Part5_ShadowMapping::Part5_ShadowMapping()
	{
		m_SimpleDepthShader = std::make_unique<Shader>("res/shader/Part5_ShadowMappingDepth.shader");
		m_DebugDepthQuadShader = std::make_unique<Shader>("res/shader/Part5_ShadowMapping_DebugQuad.shader");

		m_Cube = std::make_unique<Cube>(1.0f, "res/textures/container.jpg", *(m_SimpleDepthShader.get()));
		m_Plane = std::make_unique<Plane>(25.0f, "res/textures/wood.png", *(m_SimpleDepthShader.get()));

		m_Framebuffer = std::make_unique<Framebuffer>();
		m_Framebuffer->MakeDepthFramebuffer(1024, 1024);

		m_Screen = std::make_unique<Screen>(*(m_Framebuffer->GetTexture()));
		m_Screen->BindShader(*(m_DebugDepthQuadShader.get()));
	}

	Part5_ShadowMapping::~Part5_ShadowMapping()
	{
	}

	void Part5_ShadowMapping::OnUpdate(float deltaTime)
	{
	}

	void Part5_ShadowMapping::OnRender()
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

		glm::mat4 lightSpaceMatrix = projection * view;
		m_SimpleDepthShader->Bind();
		m_SimpleDepthShader->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);

		GLCall(glViewport(0, 0, 1024, 1024));
		m_Framebuffer->Bind();
		GLCall(glClear(GL_DEPTH_BUFFER_BIT));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, 0.0));
		m_Cube->SetTransform(model);
		m_Cube->Draw();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 1.0));
		m_Cube->SetTransform(model);
		m_Cube->Draw();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 2.0));
		model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(0.25));
		m_Cube->SetTransform(model);
		m_Cube->Draw();

		model = glm::mat4(1.0f);
		m_Plane->SetTransform(model);
		m_Plane->Draw();
		m_Framebuffer->Unbind();

		GLCall(glViewport(0, 0, 1200.0f, 800.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_DebugDepthQuadShader->Bind();
		m_DebugDepthQuadShader->SetUniform1f("near_plane", -30.0f);
		m_DebugDepthQuadShader->SetUniform1f("far_plane", 1000.0f);

		m_Screen->Draw();
	}

	void Part5_ShadowMapping::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}