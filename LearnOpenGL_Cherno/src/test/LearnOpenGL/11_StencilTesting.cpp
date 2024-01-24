#include "11_StencilTesting.h"
namespace Test {
	Part4_StencilTesting::Part4_StencilTesting()
	{
		float vertices[] = {
			//---- Œª÷√ ----    
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,

			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  1.0f,

			-0.5f, -0.5f, -0.5f, -0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -0.0f,  1.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  1.0f,

			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
		};

		unsigned int indices[] = {
			// select the top left image
			0, 1, 2,
			1, 3, 2,
			// select the top middle image
			0 + 4, 1 + 4, 2 + 4,
			1 + 4, 3 + 4, 2 + 4,
			// select to top right image
			0 + 8, 1 + 8, 2 + 8,
			1 + 8, 3 + 8, 2 + 8,
			// select the bottom left image
			0 + 12, 1 + 12, 2 + 12,
			1 + 12, 3 + 12, 2 + 12,
			// select the bottom middle image
			0 + 16, 1 + 16, 2 + 16,
			1 + 16, 3 + 16, 2 + 16,
			// select the bottom right image
			0 + 20, 1 + 20, 2 + 20,
			1 + 20, 3 + 20, 2 + 20,
		};

		float planeVertices[] = {
			// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
			 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
		};

		unsigned int planeIndex[] = {
			0, 1, 2,
			0, 2, 3,
		};

		m_CubeVAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * (3 + 2) * 4 * 6);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_CubeVAO->AddBuffer(*m_VertexBuffer, layout);
		m_VertexBuffer->Unbind();
		m_IB = std::make_unique<IndexBuffer>(indices, 36);

		m_PlaneVAO = std::make_unique<VertexArray>();
		m_PlaneVertexBuffer = std::make_unique<VertexBuffer>(planeVertices, sizeof(float) * (3 + 2) * 4 * 6);
		VertexBufferLayout planeLayout;
		planeLayout.Push<float>(3);
		planeLayout.Push<float>(2);
		m_PlaneVAO->AddBuffer(*m_PlaneVertexBuffer, planeLayout);
		m_PlaneVertexBuffer->Unbind();
		m_PlaneIB = std::make_unique<IndexBuffer>(planeIndex, 6);

		m_Shader = std::make_unique<Shader>("res/shader/Part4_DepthTesting.shader");
		m_StencilSingleShader = std::make_unique<Shader>("res/shader/Part4_StencilTesing_SingleColor.shader");

		m_Textures[0] = std::make_unique<Texture>("res/textures/marble.jpg");
		m_Textures[1] = std::make_unique<Texture>("res/textures/metal.png");

		m_Shader->Bind();
		m_Shader->SetUniform1i("texture_diffuse1", 0);

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
		m_Textures[1]->Bind();
		m_Shader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		m_PlaneVAO->Bind();
		renderer.DrawElement(*m_PlaneVAO, *m_PlaneIB, *m_Shader);

		// 1st. render pass, draw objects as normal, writing to the stencil buffer
		// --------------------------------------------------------------------
		GLCall(glStencilFunc(GL_ALWAYS, 1, 0xFF));
		GLCall(glStencilMask(0xFF));

		// cubes
		m_CubeVAO->Bind();

		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		m_Shader->SetUniformMat4f("u_Model", model);

		m_Textures[0]->Bind();
		renderer.DrawElement(*m_CubeVAO, *m_IB, *m_Shader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		m_Shader->SetUniformMat4f("u_Model", model);

		renderer.DrawElement(*m_CubeVAO, *m_IB, *m_Shader);

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
		m_CubeVAO->Bind();
		m_Textures[0]->Bind();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		m_StencilSingleShader->SetUniformMat4f("u_Model", model);
		renderer.DrawElement(*m_CubeVAO, *m_IB, *m_StencilSingleShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		m_StencilSingleShader->SetUniformMat4f("u_Model", model);
		renderer.DrawElement(*m_CubeVAO, *m_IB, *m_StencilSingleShader);

		m_CubeVAO->Unbind();

		GLCall(glStencilMask(0xFF));
		GLCall(glStencilFunc(GL_ALWAYS, 0, 0xFF));
		GLCall(glEnable(GL_DEPTH_TEST));

		/*m_PlaneVAO->Bind();
		model = glm::mat4(1.0f);
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Textures[1]->Bind();
		renderer.DrawElement(*m_PlaneVAO, *m_PlaneIB, *m_Shader);*/
	}

	void Part4_StencilTesting::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();
	}
}