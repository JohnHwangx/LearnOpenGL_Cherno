#pragma once

#include "CameraTest.h"

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

	};
}