#include "14_ShadowMapping.h"

namespace Test {

	Part5_ShadowMapping::Part5_ShadowMapping()
	{
		m_Shader = std::make_unique<Shader>("res/shader/Part5_ShadowMapping.shader");
		m_SimpleDepthShader = std::make_unique<Shader>("res/shader/Part5_ShadowMappingDepth.shader");
		//m_DebugDepthQuadShader = std::make_unique<Shader>("res/shader/Part5_ShadowMapping_DebugQuad.shader");

		m_Cube = std::make_unique<Blaze::Cube>(1.0f, 1.0f, 1.0f, "res/textures/wood.png");
		m_Plane = std::make_unique<Blaze::Plane>(25.0f, 25.0f, "res/textures/wood.png");

		m_Framebuffer = std::make_unique<Framebuffer>();
		m_Framebuffer->MakeDepthFramebuffer(1024, 1024);

		m_Shader->Bind();
		m_Shader->SetUniform1i("uTexture", 0);
		m_Shader->SetUniform1i("shadowMap", 1);
		//m_Screen = std::make_unique<Screen>(*(m_Framebuffer->GetTexture()));
		//m_Screen->BindShader(*(m_DebugDepthQuadShader.get()));
		GLCall(glEnable(GL_DEPTH_TEST));
		m_IsOthor = true;
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

		// 1. render depth of scene to texture (from light's perspective)
		// --------------------------------------------------------------
		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 1.0f, far_plane = 7.5f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(m_LightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		// render scene from light's point of view
		m_SimpleDepthShader->Bind();
		m_SimpleDepthShader->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);

		GLCall(glViewport(0, 0, 1024, 1024));
		m_Framebuffer->Bind();
		GLCall(glClear(GL_DEPTH_BUFFER_BIT));
		DrawScene(*(m_SimpleDepthShader.get()));
		m_Framebuffer->Unbind();

		GLCall(glViewport(0, 0, 1200, 800));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// 2. render scene as normal using the generated depth/shadow map  
		// --------------------------------------------------------------
		glm::mat4 view = m_Camera->GetViewMatrix();
		if (m_IsOthor)
			view = glm::scale(view, glm::vec3(m_Distance));

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 100.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 150.0f);

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("uView", view);
		m_Shader->SetUniformMat4f("uProjection", projection);
		// set light uniforms
		m_Shader->SetUniform3fv("viewPos", m_Camera->GetPosition());
		m_Shader->SetUniform3fv("lightPos", m_LightPos);
		m_Shader->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);

		m_Framebuffer->BindTexture(1);

		DrawScene(*(m_Shader.get()));

		/*m_DebugDepthQuadShader->Bind();
		m_DebugDepthQuadShader->SetUniform1f("near_plane", near_plane);
		m_DebugDepthQuadShader->SetUniform1f("far_plane", far_plane);*/

		//m_Screen->Draw();
	}

	void Part5_ShadowMapping::DrawScene(Shader& shader)
	{
		/*m_Cube->BindShader(shader);
		m_Plane->BindShader(shader);*/
		shader.Bind();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5f, 0.0));
		//m_Cube->SetTransform(model);
		shader.SetUniformMat4f("uModel", model);
		m_Cube->Draw();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 1.0));
		//m_Cube->SetTransform(model);
		shader.SetUniformMat4f("uModel", model);
		m_Cube->Draw();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 2.0));
		model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(0.5));
		//m_Cube->SetTransform(model);
		shader.SetUniformMat4f("uModel", model);
		m_Cube->Draw();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f));
		//m_Plane->SetTransform(model);
		shader.SetUniformMat4f("uModel", model);
		m_Plane->Draw();
	}

	void Part5_ShadowMapping::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}