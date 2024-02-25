#pragma once

#include "CameraTest.h"
#include "Model.h"
#include "GBufferFrameBuffer.h"
#include "Screen.h"

namespace Test {

	class Part5_DeferredShading: public CameraTest
	{
	public:
		Part5_DeferredShading();
		~Part5_DeferredShading();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:

		Model* m_Model;
		std::vector<glm::vec3> m_ObjectPositions;

		Screen* m_Screen;

		Shader* m_GeometryPassShader;
		Shader* m_LightingPassShader;
		Shader* m_LightBoxShader;
		Shader* m_FBODebug;

		GBuffer* m_GBuffer;

		std::vector<glm::vec3> m_LightPositions;
		std::vector<glm::vec3> m_LightColors;
	};
}