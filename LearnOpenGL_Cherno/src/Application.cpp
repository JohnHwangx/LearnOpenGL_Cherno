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
		testMenu->RegisterTest<Test::Part1_HelloTriangle>("Part1: Hello Triangle");
		testMenu->RegisterTest<Test::Part1_Shader>("Part1: Shader");
		testMenu->RegisterTest<Test::Part1_Shader_Interpolation>("Part1: Shader Interpolation");
		testMenu->RegisterTest<Test::Part1_Textures>("Part1: Textures");

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