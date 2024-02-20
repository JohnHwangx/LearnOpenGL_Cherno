#pragma once

#include "CameraTest.h"
#include "Shader.h"
#include "Model.h"

namespace Test {

	class Part4_AsteroidInstanced :public CameraTest
	{
	public:
		Part4_AsteroidInstanced();
		~Part4_AsteroidInstanced();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		unsigned int m_Amount;
		std::unique_ptr<Model> m_Rock;
		std::unique_ptr<Model> m_Planet;

		std::unique_ptr<Shader> m_AsteroidShader;
		std::unique_ptr<Shader> m_PlanetShader;
	};
}