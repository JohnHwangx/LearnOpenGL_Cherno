#include "08_Material.h"
#include "imgui/imgui.h"

Test::Part2_Material::Part2_Material()
{
	float vertices[] = {
		//---- Œª÷√ ----    
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,

		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,

		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
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
	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * (3 + 3+2) * 4 * 6);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_CubeVAO->AddBuffer(*m_VertexBuffer, layout);
	m_LightCubeVAO->AddBuffer(*m_VertexBuffer, layout);

	m_IB = std::make_unique<IndexBuffer>(indices, 36);

	m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

	m_LightingShader = std::make_unique<Shader>("res/shader/Part2_BasicLighting_LightingMap.shader");
	m_LightCubeShader = std::make_unique<Shader>("res/shader/Part2_BasicLighting_LightCube.shader");

	m_Textures[0] = std::make_unique<Texture>("res/textures/container2.png");
	m_Textures[1] = std::make_unique<Texture>("res/textures/container2_specular.png");

	m_LightingShader->Bind();
	m_LightingShader->SetUniform1i("material.diffuse", 0);
	m_LightingShader->SetUniform1i("material.specular", 1);
	//m_LightingShader->SetUniform1i("uTexture2", 1);

	m_LightingShader->SetUniform3fv("viewPos", m_Camera->GetPosition());

	m_Textures[0]->Bind();
	m_Textures[1]->Bind(1);
	//m_BasicMaterial = std::make_unique<BasicMaterial>(*m_LightingShader);

	GLCall(glEnable(GL_DEPTH_TEST));
}

Test::Part2_Material::~Part2_Material()
{
}

void Test::Part2_Material::OnUpdate(float deltaTime)
{
	GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	Renderer renderer;

	m_LightingShader->Bind();
	glm::mat4 r = glm::rotate(glm::mat4(1.0), deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 lp = glm::vec4(1.0f) * r;
	m_LightPos = glm::vec3(lp * m_LightDistance);
	m_LightingShader->SetUniform3fv("light.position", m_LightPos);

	// light properties
	m_LightingShader->SetUniform3f("light.ambient", m_LightAmbient[0], m_LightAmbient[1], m_LightAmbient[2]);
	m_LightingShader->SetUniform3f("light.diffuse", m_LightDiffuse[0], m_LightDiffuse[1], m_LightDiffuse[2]);
	m_LightingShader->SetUniform3f("light.specular", m_LightSpecular[0], m_LightSpecular[1], m_LightSpecular[2]);

	// material properties
	m_LightingShader->SetUniform1f("material.shininess", m_Shininess);

	glm::mat4 view = m_Camera->GetViewMatrix();
	if (m_IsOthor)
		view = glm::scale(view, glm::vec3(m_Distance));

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
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	m_LightCubeShader->SetUniformMat4f("u_Model", model);
	m_LightCubeShader->SetUniformMat4f("u_View", view);
	m_LightCubeShader->SetUniformMat4f("u_Projection", projection);

	renderer.DrawElement(*m_LightCubeVAO, *m_IB, *m_LightCubeShader);
}

void Test::Part2_Material::OnRender()
{
}

void Test::Part2_Material::OnImGuiRender()
{
	ImGui::Checkbox("IsOthor", &m_IsOthor);
	if (ImGui::DragFloat("Yaw", &m_Yaw, 1.0f, -180.0f, 180.0f))
	{
		m_Camera->CameraYaw(m_Yaw);
	}

	if (ImGui::DragFloat("Pitch", &m_Pitch, 1.0f, -89.9f, 89.9f))
	{
		m_Camera->CameraPitch(m_Pitch);
	}

	if (ImGui::DragFloat("Distance", &m_Distance, 0.1f, 0.1f, 30.0f))
	{
		m_Camera->SetDistance(m_Distance);
	}
	ImGui::Text("Material");
	ImGui::DragFloat3("Ambient", &m_Ambient[0], 0.05f, 0.0f, 1.0f);
	ImGui::DragFloat3("Diffuse", &m_Diffuse[0], 0.05f, 0.0f, 1.0f);
	ImGui::DragFloat3("Specular", &m_Specular[0], 0.05f, 0.0f, 1.0f);
	ImGui::DragFloat("Shininess", &m_Shininess, 0.1f, 0.0f, 64.0f);
	ImGui::Text("Light");
	ImGui::DragFloat3("Light Ambient", &m_LightAmbient[0], 0.05f, 0.0f, 1.0f);
	ImGui::DragFloat3("Light Diffuse", &m_LightDiffuse[0], 0.05f, 0.0f, 1.0f);
	ImGui::DragFloat3("Light Specular", &m_LightSpecular[0], 0.05f, 0.0f, 1.0f);
}
