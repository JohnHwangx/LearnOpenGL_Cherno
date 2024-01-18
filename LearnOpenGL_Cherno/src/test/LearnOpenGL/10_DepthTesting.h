#pragma once

#include "test/Test.h"

namespace Test {
	class Part4_DepthTesting: public Test
	{
	public:
		Part4_DepthTesting();
		~Part4_DepthTesting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:

	};
}