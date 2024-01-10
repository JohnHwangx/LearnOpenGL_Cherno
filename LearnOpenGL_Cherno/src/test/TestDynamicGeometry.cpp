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

		const size_t MaxQuadCount = 1000;
		const size_t MaxVertexCount = MaxQuadCount * 4;
		const size_t MaxIndexCount = MaxQuadCount * 6;


		GLCall(glCreateVertexArrays(1, &m_QuadVA));
		GLCall(glBindVertexArray(m_QuadVA));

		GLCall(glCreateBuffers(1, &m_QuadVB));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertexCount, nullptr, GL_DYNAMIC_DRAW));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position)));

		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color)));

		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord)));

		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexId)));

		//unsigned int indices[] = {
		//	0, 1, 2, 2, 3, 0,
		//	4, 5, 6, 6, 7, 4
		//};

		uint32_t indices[MaxIndexCount];
		uint32_t offset = 0;
		for (size_t i = 0; i < MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

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

	static Vertex* CreateQaud(Vertex* target, float x, float y, float texId)
	{
		float size =1.0f;

		target->Position = { x, y, 0.0f };
		target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->TexCoord = { 0.0f, 0.0f };
		target->TexId = texId;
		target++;

		target->Position = { x + size, y, 0.0f };
		target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->TexCoord = { 1.0f, 0.0f };
		target->TexId = texId;
		target++;

		target->Position = { x + size, y + size, 0.0f };
		target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->TexCoord = { 1.0f, 1.0f };
		target->TexId = texId;
		target++;

		target->Position = { x, y + size, 0.0f };
		target->Color = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->TexCoord = { 0.0f, 1.0f };
		target->TexId = texId;
		target++;

		return target;
	}

	void TestDynamicGeometry::OnRender()
	{

		GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		uint32_t indexCount = 0;

		std::array<Vertex, 1000> vertices;
		Vertex* buffer = vertices.data();
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				buffer = CreateQaud(buffer, x, y, (x + y) % 2);
				indexCount += 6;
			}
		}

		buffer = CreateQaud(buffer, m_Position[0], m_Position[1], 0.0f);
		indexCount += 6;

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()));

		GLCall(glUseProgram(m_Shader->GetRendererID()));
		GLCall(glBindTextureUnit(0, m_Texture[0]->GetRendererId()));
		GLCall(glBindTextureUnit(1, m_Texture[1]->GetRendererId()));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 100.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f));
		glm::mat4 mvp = m_Proj * m_View * model;

		m_Shader->SetUniformMat4f("u_MVP", mvp);

		GLCall(glBindVertexArray(m_QuadVA));
		GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
	}

	void TestDynamicGeometry::OnImGuiRender()
	{
		ImGui::DragFloat2("Quad Position", m_Position, 0.1f);
	}
}