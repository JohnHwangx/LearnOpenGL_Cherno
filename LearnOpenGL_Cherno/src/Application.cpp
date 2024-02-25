#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"
#include "test/TestBatchRender.h"
#include "test/TestDynamicGeometry.h"
#include "test/LearnOpenGL/01_HelloTriangle.h"
#include "test/LearnOpenGL/02_Shader.h"
#include "test/LearnOpenGL/02_Shader_Interpolation.h"
#include "test/LearnOpenGL/03_Textures.h"
#include "test/LearnOpenGL/04_Transformation.h"
#include "test/LearnOpenGL/05_CoordinationSystem.h"
#include "test/LearnOpenGL/06_Camera.h"
#include "test/LearnOpenGL/07_Basic_Lighting.h"
#include "test/LearnOpenGL/08_Material.h"
#include "test/LearnOpenGL/09_LoadingModel.h"
#include "test/LearnOpenGL/10_DepthTesting.h"
#include "test/LearnOpenGL/11_StencilTesting.h"
#include "test/LearnOpenGL/12_Blending.h"
#include "test/LearnOpenGL/13_Framebuffers.h"
#include "test/LearnOpenGL/14_ShadowMapping.h"
#include "test/LearnOpenGL/15_Cubemaps.h"
#include "test/LearnOpenGL/16_AsteroidsInstanced.h"
#include "test/LearnOpenGL/17_DeferredShading.h"
#include "test/TestCube2.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1200, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR!" << std::endl;
	}
	unsigned char* glVersion;
	GLCall(glVersion = (unsigned char*)glGetString(GL_VERSION));
	std::cout << "Status: Using GL " << glVersion << std::endl;
	{
		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();
		ImGui::StyleColorsDark();

		Test::Test* currentTest;
		Test::TestMenu* testMenu = new Test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<Test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<Test::TestTexture2D>("2D Texture");
		testMenu->RegisterTest<Test::TestBatchRender>("Batch Render");
		testMenu->RegisterTest<Test::TestDynamicGeometry>("Dynamic Geometry");
		testMenu->RegisterTest<Test::TestCube2>("Cube2");
		testMenu->RegisterTest<Test::Part1_HelloTriangle>("Part1: Hello Triangle");
		testMenu->RegisterTest<Test::Part1_Shader>("Part1: Shader");
		testMenu->RegisterTest<Test::Part1_Shader_Interpolation>("Part1: Shader Interpolation");
		testMenu->RegisterTest<Test::Part1_Textures>("Part1: Textures");
		testMenu->RegisterTest<Test::Part1_Transformation>("Part1: Transformation");
		testMenu->RegisterTest<Test::Part1_CoodinationSystem>("Part1: Coodination System");
		testMenu->RegisterTest<Test::Part1_Camera>("Part1: Camera");
		testMenu->RegisterTest<Test::Part2_BasicLighting>("Part2: Basic Lighting");
		testMenu->RegisterTest<Test::Part2_Material>("Part2: Material");
		testMenu->RegisterTest<Test::Part3_LoadingModel>("Part3: Loading Model");
		testMenu->RegisterTest<Test::Part4_DepthTesting>("Part4: Depth Testing");
		testMenu->RegisterTest<Test::Part4_StencilTesting>("Part4: Stencil Testing");
		testMenu->RegisterTest<Test::Part4_Blending>("Part4: Blending");
		testMenu->RegisterTest<Test::Part4_FrameBuffer>("Part4: Framebuffers");
		testMenu->RegisterTest<Test::Part4_Cubemaps>("Part4: Cubemaps");
		testMenu->RegisterTest<Test::Part4_AsteroidInstanced>("Part4: Asteroid Instanced");
		testMenu->RegisterTest<Test::Part5_DeferredShading>("Part5: Deferred Shading");
		testMenu->RegisterTest<Test::Part5_ShadowMapping>("Part5: Shadow Mapping");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			/* Render here */
			renderer.Clear();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				float timeValue = glfwGetTime();
				currentTest->OnUpdate(timeValue);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}