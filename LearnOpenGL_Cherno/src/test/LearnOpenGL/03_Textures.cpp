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

		m_TextureIds[0] = GetTexture("res/textures/imageLena_512.png");
		m_TextureIds[1] = GetTexture("res/textures/imageLena_300.png");
		m_TextureIds[2] = GetTexture("res/textures/imageUV_256.png");

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
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		float scale[] = { powf(m_Scale, 2) };
		m_Shader->SetUniform1fv("uScale", 1, scale);

		//m_Texture->Bind();
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureIds[m_TextureIndex]));

		if (m_WrapIndex == 0) 
		{
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		}
		else
		{
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		}

		if (m_MagFilterIndex == 0)
		{
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		}
		else
		{
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		}

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
	
	unsigned int Part1_Textures::GetTexture(const std::string& path)
	{
		unsigned int textureId;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* localBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		GLCall(glGenTextures(1, &textureId));
		GLCall(glBindTexture(GL_TEXTURE_2D, textureId));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (localBuffer)
			stbi_image_free(localBuffer);

		return textureId;
	}
}