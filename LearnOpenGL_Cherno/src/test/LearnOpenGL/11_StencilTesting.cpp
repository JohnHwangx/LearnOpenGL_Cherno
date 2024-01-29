#include "11_StencilTesting.h"
namespace Test {
	Part4_StencilTesting::Part4_StencilTesting()
	{
		m_Shader = std::make_unique<Shader>("res/shader/Part4_DepthTesting.shader");
		m_StencilSingleShader = std::make_unique<Shader>("res/shader/Part4_StencilTesing_SingleColor.shader");

		m_Cube = std::make_unique<Cube>(*(m_Shader.get()));
		m_StencilCube = std::make_unique<Cube>(*(m_StencilSingleShader.get()));
		m_Plane = std::make_unique<Plane>(*(m_Shader.get()));

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
		GLCall(glEnable(GL_STENCIL_TEST));
		GLCall(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
		GLCall(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
	}

	Part4_StencilTesting::~Part4_StencilTesting()
	{
	}

	void Part4_StencilTesting::OnUpdate(float deltaTime)
	{
	}

	void Part4_StencilTesting::OnRender()
	{
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

		Renderer renderer;
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = m_Camera->GetViewMatrix();
		if (m_IsOthor)
			view = glm::scale(view, glm::vec3(m_Distance));

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 1000.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

		m_StencilSingleShader->Bind();
		m_StencilSingleShader->SetUniformMat4f("u_View", view);
		m_StencilSingleShader->SetUniformMat4f("u_Projection", projection);

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_View", view);
		m_Shader->SetUniformMat4f("u_Projection", projection);

		// draw floor as normal, but don't write the floor to the stencil buffer, we only care about the containers. We set its mask to 0x00 to not write to the stencil buffer.
		GLCall(glStencilMask(0x00));
		// floor
		//m_Shader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		m_Plane->SetTransform(glm::mat4(1.0f));
		m_Plane->Draw();

		// 1st. render pass, draw objects as normal, writing to the stencil buffer
		// --------------------------------------------------------------------
		GLCall(glStencilFunc(GL_ALWAYS, 1, 0xFF));
		GLCall(glStencilMask(0xFF));

		// cubes
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		m_Cube->SetTransform(model);
		m_Cube->Draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		m_Cube->SetTransform(model);
		m_Cube->Draw();

		// 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
		// Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing 
		// the objects' size differences, making it look like borders.
		// -----------------------------------------------------------------------------------------------------------------------------
		GLCall(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
		GLCall(glStencilMask(0x00));
		GLCall(glDisable(GL_DEPTH_TEST));

		m_StencilSingleShader->Bind();

		float scale = 1.1f;

		// cubes
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		m_StencilCube->SetTransform(model);
		m_StencilCube->Draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		m_StencilCube->SetTransform(model);
		m_StencilCube->Draw();

		GLCall(glStencilMask(0xFF));
		GLCall(glStencilFunc(GL_ALWAYS, 0, 0xFF));
		GLCall(glEnable(GL_DEPTH_TEST));
	}

	void Part4_StencilTesting::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}