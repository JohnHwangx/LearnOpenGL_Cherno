#include "03_Textures.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

#include <vendor/stb_image/stb_image.h>

namespace Test {

	Part1_Textures::Part1_Textures()
		: m_Scale(1.0f), m_TextureIndex(0), m_WrapIndex(0), m_MagFilterIndex(0), m_MinFilterIndex(0)
	{
		float vertices[] = {
			 //---- 位置 ----      ---- 颜色 ----     - 纹理坐标 -
			-1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			-1.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			 1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			 1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(float) * 8 * 4);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IB = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shader/Part1_Textures.shader");

		m_Shader->Bind();

		m_Textures[0] = std::make_unique<Texture>("res/textures/imageLena_512.png");
		m_Textures[1] = std::make_unique<Texture>("res/textures/imageLena_300.png");
		m_Textures[2] = std::make_unique<Texture>("res/textures/imageUV_256.png");

		m_Shader->SetUniform1i("uTexture", 0);

		float resolution[] = { 1200.0f, 800.0f };
		m_Shader->SetUniform2fv("uResolution", 1, resolution);
		float scale[] = { powf(m_Scale, 2) };
		m_Shader->SetUniform1fv("uScale", 1, scale);
	}

	Part1_Textures::~Part1_Textures()
	{
	}

	void Part1_Textures::OnUpdate(float deltaTime)
	{
	}

	void Part1_Textures::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		m_Textures[m_TextureIndex]->Unbind();

		float scale[] = { powf(m_Scale, 2) };
		m_Shader->SetUniform1fv("uScale", 1, scale);

		m_Textures[m_TextureIndex]->Bind();
		m_Textures[m_TextureIndex]->SetTextureWrap(m_WrapIndex == 0 ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		m_Textures[m_TextureIndex]->SetTextureMagFilter(m_MagFilterIndex == 0 ? GL_LINEAR : GL_NEAREST);

		Renderer renderer;

		renderer.DrawElement(*m_VAO, *m_IB, *m_Shader);
	}

	void Part1_Textures::OnImGuiRender()
	{
		const char* textureItems[] = { "512","300" };
		ImGui::Combo("Size", &m_TextureIndex, textureItems, IM_ARRAYSIZE(textureItems));
		ImGui::DragFloat("Scale", &m_Scale, 0.1f, 0.0f, 2.0f);
		const char* wrapItems[] = { "CLAMP","REPEAT" };
		ImGui::Combo("Wrap", &m_WrapIndex, wrapItems, IM_ARRAYSIZE(wrapItems));

		const char* magFilterItems[] = { "LINEAR","NEAREST" };
		ImGui::Combo("MAG_FILTER", &m_MagFilterIndex, magFilterItems, IM_ARRAYSIZE(magFilterItems));
	}
}