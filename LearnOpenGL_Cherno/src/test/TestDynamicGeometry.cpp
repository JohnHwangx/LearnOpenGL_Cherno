#include "TestDynamicGeometry.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <array>

namespace Test {

	struct Vec2
	{
		float x, y;
	};
	struct Vec3
	{
		float x, y, z;
	};
	struct Vec4
	{
		float r, g, b, a;
	};
	struct Vertex
	{
		Vec3 Position;
		Vec4 Color;
		Vec2 TexCoord;
		float TexId;
	};

	TestDynamicGeometry::TestDynamicGeometry()
		:m_Proj(glm::ortho(0.0f, 950.0f, 0.0f, 680.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)))
	{
		m_Shader = std::make_unique<Shader>("res/shader/BatchRender.shader");

		glUseProgram(m_Shader->GetRendererID());
		auto loc = glGetUniformLocation(m_Shader->GetRendererID(), "u_Textures");
		int samplers[2] = { 0, 1 };

		glUniform1iv(loc, 2, samplers);

		GLCall(glCreateVertexArrays(1, &m_QuadVA));
		GLCall(glBindVertexArray(m_QuadVA));

		GLCall(glCreateBuffers(1, &m_QuadVB));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));

		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));

		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord)));

		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexId)));

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		GLCall(glCreateBuffers(1, &m_QuadIB));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadIB));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

		m_Texture[0] = std::make_unique<Texture>("res/textures/ChernoLogo.png");
		m_Texture[1] = std::make_unique<Texture>("res/textures/HazelLogo.png");
	}
	TestDynamicGeometry::~TestDynamicGeometry()
	{
	}
	void TestDynamicGeometry::OnUpdate(float deltaTime)
	{
	}

	static std::array<Vertex, 4> CreateQaud(float x, float y, float texId)
	{
		float size = 2.0f;

		Vertex v0;
		v0.Position = { x, y, 0.0f };
		v0.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		v0.TexCoord = { 0.0f, 0.0f };
		v0.TexId = texId;

		Vertex v1;
		v1.Position = { x + size, y, 0.0f };
		v1.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		v1.TexCoord = { 1.0f, 0.0f };
		v1.TexId = texId;

		Vertex v2;
		v2.Position = { x + size, y + size, 0.0f };
		v2.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		v2.TexCoord = { 1.0f, 1.0f };
		v2.TexId = texId;

		Vertex v3;
		v3.Position = { x, y + size, 0.0f };
		v3.Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		v3.TexCoord = { 0.0f, 1.0f };
		v3.TexId = texId;

		return { v0,v1,v2,v3 };
	}

	void TestDynamicGeometry::OnRender()
	{

		GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		auto q0 = CreateQaud(m_Position[0], m_Position[1], 0.0f);
		auto q1 = CreateQaud(0.5f, -0.5f, 1.0f);

		Vertex vertices[8];
		memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
		memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));

		GLCall(glUseProgram(m_Shader->GetRendererID()));
		GLCall(glBindTextureUnit(0, m_Texture[0]->GetRendererId()));
		GLCall(glBindTextureUnit(1, m_Texture[1]->GetRendererId()));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 400.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f));
		glm::mat4 mvp = m_Proj * m_View * model;

		m_Shader->SetUniformMat4f("u_MVP", mvp);

		GLCall(glBindVertexArray(m_QuadVA));
		GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));
	}

	void TestDynamicGeometry::OnImGuiRender()
	{
		ImGui::DragFloat2("Quad Position", m_Position, 0.1f);
	}
}