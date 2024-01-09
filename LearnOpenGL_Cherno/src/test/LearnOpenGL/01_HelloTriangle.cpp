#include "01_HelloTriangle.h"
#include "imgui/imgui.h"

namespace Test {

	Part1_HelloTriangle::Part1_HelloTriangle()
	{
		float vertices[] = {
			 -0.5f, -0.5f, 0.0f, // left  
			 0.5f, -0.5f, 0.0f, // right 
			 0.0f,  0.5f, 0.0f  // top 
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * 3 * 3); 
		VertexBufferLayout layout;
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = std::make_unique<Shader>("res/shader/Part1_Simple.shader");

	}

	Part1_HelloTriangle::~Part1_HelloTriangle()
	{
	}

	void Part1_HelloTriangle::OnUpdate(float deltaTime)
	{
	}

	void Part1_HelloTriangle::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		renderer.DrawArray(*m_VAO, *m_Shader, 3);
	}

	void Part1_HelloTriangle::OnImGuiRender()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}
}