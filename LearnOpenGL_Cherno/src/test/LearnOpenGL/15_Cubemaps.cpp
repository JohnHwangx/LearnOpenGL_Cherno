#include "15_Cubemaps.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Test {
	Part4_Cubemaps::Part4_Cubemaps()
		:m_Mode(NORMAL)
	{
		m_Shader = std::make_unique<Shader>("res/shader/Part4_Cubemaps.shader");
		m_SkyboxShader = std::make_unique<Shader>("res/shader/Part4_Skybox.shader");

		m_ReflectShader = std::make_unique<Shader>("res/shader/Part4_Cubemaps_Reflect.shader");
		m_RefractShader = std::make_unique<Shader>("res/shader/Part4_Cubemaps_Refract.shader");

		m_Texture = std::make_unique<Texture>("res/textures/container.jpg");

		m_Cube = std::make_unique<Blaze::Cube>(1.0f, 1.0f, 1.0f, m_Texture.get());

		m_Shader->Bind();
		m_Shader->SetUniform1i("texture_diffuse1", 0);

		m_ReflectShader->Bind();
		m_ReflectShader->SetUniform1i("skybox", 0);
		m_RefractShader->Bind();
		m_RefractShader->SetUniform1i("skybox", 0);

		m_Skybox = std::make_unique<Skybox>();

		GLCall(glEnable(GL_DEPTH_TEST));
	}
	Part4_Cubemaps::~Part4_Cubemaps()
	{
	}
	void Part4_Cubemaps::OnUpdate(float deltaTime)
	{
	}
	void Part4_Cubemaps::OnRender()
	{
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		glm::mat4 view = m_Camera->GetViewMatrix();
		if (m_IsOthor)
			view = glm::scale(view, glm::vec3(m_Distance));

		glm::mat4 projection(1.0f);
		if (m_IsOthor)
			projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 100.0f);
		else
			projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 150.0f);

		Shader* shader = m_Shader.get();
		
		if(m_Mode==REFLECT)
		{
			shader = m_ReflectShader.get();
			shader->Bind();
			shader->SetUniform3fv("cameraPos", m_Camera->GetPosition());
			m_Skybox->BindTexture();
		}
		else if (m_Mode == REFRACT)
		{
			shader = m_RefractShader.get();
			shader->Bind();
			shader->SetUniform3fv("cameraPos", m_Camera->GetPosition());
			m_Skybox->BindTexture();
		}

		shader->Bind();
		shader->SetUniformMat4f("uView", view);
		shader->SetUniformMat4f("uProjection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		shader->SetUniformMat4f("uModel", model);
		m_Cube->Draw();

		view = glm::mat4(glm::mat3(m_Camera->GetViewMatrix()));
		projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 150.0f);
		m_Skybox->Draw(view, projection);
	}

	void Part4_Cubemaps::OnImGuiRender()
	{
		this->CameraTest::OnImGuiRender();

		if (ImGui::Button("Normal")) 
		{
			m_Mode = NORMAL;
		}
		else if (ImGui::Button("Reflect"))
		{
			m_Mode = REFLECT;
		}
		else if (ImGui::Button("Refract"))
		{
			m_Mode = REFRACT;
		}
	}
}