#pragma once

#include "LearnOpenGL/CameraTest.h"
#include "Blaze/Cube2.h"
#include "Blaze/Triangle.h"
#include "Blaze/Plane2.h"
#include "Texture.h"

namespace Test {
	class TestCube2 : public CameraTest
	{
	public:
		TestCube2();
		~TestCube2();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Shader> m_Shader;
		//std::unique_ptr<Texture> m_Texture;
		//std::unique_ptr<Texture> m_PlaneTexture;

		std::unique_ptr<Blaze::Cube> m_Cube;
		std::unique_ptr<Blaze::Triangle> m_Triangle;
		std::unique_ptr<Blaze::Plane> m_Plane;

		float m_DeltaTime = 0.0f; // 当前帧与上一帧的时间差
		float m_LastFrame = 0.0f; // 上一帧的时间
	};
}