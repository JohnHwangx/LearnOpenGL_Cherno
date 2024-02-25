#include "17_DeferredShading.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Test {

	Part5_DeferredShading::Part5_DeferredShading()
	{
		m_GeometryPassShader = new Shader("res/shader/Part5_DeferredShading/Part5_G_Buffer.shader");
		m_LightingPassShader = new Shader("res/shader/Part5_DeferredShading/Part5_Deferred_Shading.shader");
		m_LightBoxShader = new Shader("res/shader/Part5_DeferredShading/Part5_Deferred_Light_Box.shader");
		m_FBODebug = new Shader("res/shader/Part5_DeferredShading/Part5_Fbo_Debug.shader");

		m_Model = new Model("res/models/nanosuit/nanosuit.obj");
		m_ObjectPositions.push_back(glm::vec3(-3.0, -3.5, -3.0));
		m_ObjectPositions.push_back(glm::vec3(0.0, -3.5, -3.0));
		m_ObjectPositions.push_back(glm::vec3(3.0, -3.5, -3.0));
		m_ObjectPositions.push_back(glm::vec3(-3.0, -3.5, 0.0));
		m_ObjectPositions.push_back(glm::vec3(0.0, -3.5, 0.0));
		m_ObjectPositions.push_back(glm::vec3(3.0, -3.5, 0.0));
		m_ObjectPositions.push_back(glm::vec3(-3.0, -3.5, 3.0));
		m_ObjectPositions.push_back(glm::vec3(0.0, -3.5, 3.0));
		m_ObjectPositions.push_back(glm::vec3(3.0, -3.5, 3.0));

		m_GBuffer = new GBuffer(1200, 800);

		// lighting info
		// -------------
		const unsigned int NR_LIGHTS = 32;
		srand(13);
		for (unsigned int i = 0; i < NR_LIGHTS; i++)
		{
			// calculate slightly random offsets
			float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
			float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
			float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
			m_LightPositions.push_back(glm::vec3(xPos, yPos, zPos));
			// also calculate random color
			float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
			float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
			float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
			m_LightColors.push_back(glm::vec3(rColor, gColor, bColor));
		}

		// shader configuration
		// --------------------
		m_LightingPassShader->Bind();
		m_LightingPassShader->SetUniform1i("gPosition", 0);
		m_LightingPassShader->SetUniform1i("gNormal", 1);
		m_LightingPassShader->SetUniform1i("gAlbedoSpec", 2);

		m_FBODebug->Bind();
		m_FBODebug->SetUniform1i("fboAttachment", 0);

		m_Screen = new Screen();
		m_Cube = new Cube(1.0f);

	}

	Part5_DeferredShading::~Part5_DeferredShading()
	{
		delete m_Model;
		delete m_GBuffer;
		delete m_Screen;

		delete m_GeometryPassShader;
		delete m_LightBoxShader;
		delete m_LightingPassShader;
	}

	void Part5_DeferredShading::OnUpdate(float deltaTime)
	{
		// render
        // ------
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glm::mat4 view = m_Camera->GetViewMatrix();
		if (m_IsOthor)
			view = glm::scale(view, glm::vec3(m_Distance));

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 1000.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 1500.0f);

		glm::mat4 model = glm::mat4(1.0f);

		// 1. geometry pass: render scene's geometry/color data into gbuffer
		// -----------------------------------------------------------------
		m_GBuffer->Bind();
		{
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			m_GeometryPassShader->Bind();
			m_GeometryPassShader->SetUniformMat4f("projection", projection);
			m_GeometryPassShader->SetUniformMat4f("view", view);
			m_Model->BindShader(*m_GeometryPassShader);
			for (unsigned int i = 0; i < m_ObjectPositions.size(); i++)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, m_ObjectPositions[i]);
				model = glm::scale(model, glm::vec3(0.5f));
				m_GeometryPassShader->SetUniformMat4f("model", model);
				m_Model->Draw();
			}
		}
		m_GBuffer->Unbind();

		// 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
		// ------------------------------------------------------------------------------------------------------------
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		m_LightingPassShader->Bind();
		//m_FBODebug->Bind();

		m_GBuffer->ActiveTextures();
		// send light relevant uniforms
		for (unsigned int i = 0; i < m_LightPositions.size(); i++)
		{
			m_LightingPassShader->SetUniform3fv("lights[" + std::to_string(i) + "].Position", m_LightPositions[i]);
			m_LightingPassShader->SetUniform3fv("lights[" + std::to_string(i) + "].Color", m_LightPositions[i]);
			// update attenuation parameters and calculate radius
			const float linear = 0.7;
			const float quadratic = 1.8;
			m_LightingPassShader->SetUniform1f("lights[" + std::to_string(i) + "].Linear", linear);
			m_LightingPassShader->SetUniform1f("lights[" + std::to_string(i) + "].Quadratic", quadratic);
		}
		m_LightingPassShader->SetUniform3fv("viewPos", m_Camera->GetPosition());

		m_Screen->BindShader(*m_LightingPassShader);
		//m_Screen->BindShader(*m_FBODebug);
		m_Screen->Draw();

		// 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
		// ----------------------------------------------------------------------------------
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_GBuffer->GetRendererID());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
		// blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
		// the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
		// depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
		glBlitFramebuffer(0, 0, 1200, 800, 0, 0, 1200, 800, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 3. render lights on top of scene
		// --------------------------------
		m_LightBoxShader->Bind();
		m_LightBoxShader->SetUniformMat4f("projection", projection);
		m_LightBoxShader->SetUniformMat4f("view", view);
		m_Cube->BindShader(*m_LightBoxShader);
		for (unsigned int i = 0; i < m_LightPositions.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, m_LightPositions[i]);
			model = glm::scale(model, glm::vec3(0.125f));
			m_LightBoxShader->SetUniformMat4f("model", model);
			m_LightBoxShader->SetUniform3fv("lightColor", m_LightPositions[i]);
			//renderCube();
			m_Cube->Draw();
		}
	}

	void Part5_DeferredShading::OnRender()
	{
	}

	void Part5_DeferredShading::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}