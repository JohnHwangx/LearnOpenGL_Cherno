#pragma once

#include "CameraTest.h"
#include "Blaze/Cube2.h"
#include "Shader.h"
#include "Skybox.h"

namespace Test {

	enum Mode
	{
		NORMAL,
		REFLECT,
		REFRACT
	};

	class Part4_Cubemaps:public CameraTest
	{
	public:
		Part4_Cubemaps();
		~Part4_Cubemaps();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		Mode m_Mode;
		std::unique_ptr<Blaze::Cube> m_Cube;

		std::unique_ptr<Skybox> m_Skybox;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_ReflectShader;
		std::unique_ptr<Shader> m_RefractShader; 
		std::unique_ptr<Shader> m_SkyboxShader;
		std::unique_ptr<Texture> m_Texture;
	};
}