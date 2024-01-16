#pragma once
#include "test/Test.h"

namespace Test {
	class Part3_LoadingModel :public Test
	{
	public:
		Part3_LoadingModel();
		~Part3_LoadingModel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:

	};
}