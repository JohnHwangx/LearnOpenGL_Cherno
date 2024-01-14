#include "07_Basic_Lighting.h"
#include "imgui/imgui.h"

Test::Part2_BasicLighting::Part2_BasicLighting()
{
	float vertices[] = {
		//---- λ�� ----    
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
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

	m_CubeVAO = std::make_unique<VertexArray>();
	m_LightCubeVAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * 3 * 4 * 6);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	m_CubeVAO->AddBuffer(*m_VertexBuffer, layout);
	m_LightCubeVAO->AddBuffer(*m_VertexBuffer, layout);

	m_IB = std::make_unique<IndexBuffer>(indices, 36);

	m_LightingShader = std::make_unique<Shader>("res/shader/Part2_BasicLighting_Color.shader");
	m_LightCubeShader = std::make_unique<Shader>("res/shader/Part2_BasicLighting_LightCube.shader");

	m_LightingShader->Bind();
	m_LightingShader->SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
	m_LightingShader->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);

	m_Camera = std::make_unique<Camera>();
}

Test::Part2_BasicLighting::~Part2_BasicLighting()
{
}

void Test::Part2_BasicLighting::OnUpdate(float deltaTime)
{
}

void Test::Part2_BasicLighting::OnRender()
{
	GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	Renderer renderer;

	glm::mat4 view = m_Camera->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection(1.0f);
	if (m_IsOthor)
		projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 1000.0f);
	else
		projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

	m_LightingShader->Bind();
	m_LightingShader->SetUniformMat4f("u_Model", model);
	m_LightingShader->SetUniformMat4f("u_View", view);
	m_LightingShader->SetUniformMat4f("u_Projection", projection);

	renderer.DrawElement(*m_CubeVAO, *m_IB, *m_LightingShader);

	m_LightCubeShader->Bind();
	model = glm::mat4(1.0f);
	model = glm::translate(model, m_LightPos);
	model = glm::scale(model, glm::vec3(1.2f)); // a smaller cube
	m_LightCubeShader->SetUniformMat4f("u_Model", model);
	m_LightCubeShader->SetUniformMat4f("u_View", view);
	m_LightCubeShader->SetUniformMat4f("u_Projection", projection);

	renderer.DrawElement(*m_LightCubeVAO, *m_IB, *m_LightCubeShader);
}

void Test::Part2_BasicLighting::OnImGuiRender()
{
	ImGui::Checkbox("Demo Window", &m_IsOthor);
	if (ImGui::DragFloat("Yaw", &m_Yaw, 1.0f, -89.9f, 89.9f))
	{
		m_Camera->CameraYaw(m_Yaw);
	}

	if (ImGui::DragFloat("Pitch", &m_Pitch, 1.0f, -89.9f, 89.9f))
	{
		m_Camera->CameraPitch(m_Pitch);
	}

	if (ImGui::DragFloat(" Distance", &m_Distance, 0.1f, 0.1f, 30.0f))
	{
		m_Camera->SetDistance(m_Distance);
	}
}
