#include "TestBatchRender.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Test::TestBatchRender::TestBatchRender()
	:m_Proj(glm::ortho(0.0f, 950.0f, 0.0f, 680.0f, -1.0f, 1.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)))
{

	float vertices[] = {
		 0.5f, -1.0f, 0.0f,
		 2.5f, -1.0f, 0.0f,
		 2.5f,  1.0f, 0.0f,
		 0.5f,  1.0f, 0.0f,

		-2.5f, -1.0f, 0.0f,
		-0.5f, -1.0f, 0.0f,
		-0.5f,  1.0f, 0.0f,
		-2.5f,  1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * 3 * 4 * 2);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);

	m_IndexBUffer = std::make_unique<IndexBuffer>(indices, 6 * 2);

	m_Shader = std::make_unique<Shader>("res/shader/BatchRender.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.9f, 0.3f, 0.8f, 1.0f);
}

Test::TestBatchRender::~TestBatchRender()
{
}

void Test::TestBatchRender::OnUpdate(float deltaTime)
{
}

void Test::TestBatchRender::OnRender()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	Renderer renderer;

	m_Shader->Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 400.0f, 0.0f));
	model = glm::scale(model, glm::vec3(100.0f));
	glm::mat4 mvp = m_Proj * m_View * model;

	m_Shader->SetUniformMat4f("u_MVP", mvp);

	renderer.Draw(*m_VAO, *m_IndexBUffer, *m_Shader);
}

void Test::TestBatchRender::OnImGuiRender()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
}
