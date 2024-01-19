#pragma once


#include "test/Test.h"

namespace Test {
	class Part4_StencilTesting : public Test
	{
	public:
		Part4_StencilTesting();
		~Part4_StencilTesting();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:

	};
}