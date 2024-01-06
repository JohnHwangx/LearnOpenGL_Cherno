#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
	window = glfwCreateWindow(950, 680, "Hello World", NULL, NULL);
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
		float vertex[] = {
			-1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 1.0f,
		};

		float vertex2[] = {
			-0.2f, -0.2f, 0.0f, 0.0f, 0.0f,
			 0.8f, -0.2f, 0.0f, 1.0f, 0.0f,
			 0.8f,  0.8f, 0.0f, 1.0f, 1.0f,
			-0.2f,  0.8f, 0.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		VertexBuffer vb(vertex, sizeof(float) * 4 * 4);
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		VertexArray va2;
		VertexBuffer vb2(vertex2, sizeof(float) * 6 * 4);
		VertexBufferLayout layout2;
		layout2.Push<float>(3);
		layout2.Push<float>(2);
		va2.AddBuffer(vb2, layout2);

		IndexBuffer ibo(indices, 6);

		glm::mat4 proj = glm::ortho(0.0f, 950.0f, 0.0f, 680.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 300.0f, 0.0f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));//先平移后缩放
		model = glm::scale(model, glm::vec3(100.0f));
		glm::mat4 mvp = proj * view * model;

		Shader shader("res/shader/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.9f, 0.3f, 0.8f, 1.0f);

		Texture texture("res/textures/ChernoLogo.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);
		shader.SetUniformMat4f("u_MVP", mvp);

		va.Unbind();
		va2.Unbind();
		vb.Unbind();
		vb2.Unbind();
		ibo.Unbind();
		shader.Unbind();

		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		float r = 0.0f;
		float increment = 0.05f;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			//if ( r < 0.5f)
				renderer.Draw(va, ibo, shader);
			//else
				//renderer.Draw(va2, ibo, shader);

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}