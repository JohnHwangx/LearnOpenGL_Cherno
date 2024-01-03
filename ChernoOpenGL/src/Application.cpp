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

struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

//static ShaderProgramSource ParseShader(const std::string& filepath)
//{
//	std::ifstream stream(filepath);
//
//	enum class ShaderType
//	{
//		NONE = -1, VERTEX = 0, FRAGMENT = 1
//	};
//
//	std::string line;
//	std::stringstream ss[2];
//	ShaderType type = ShaderType::NONE;
//	while (getline(stream, line))
//	{
//		if (line.find("#shader") != std::string::npos) {
//			if (line.find("vertex") != std::string::npos)
//				type = ShaderType::VERTEX;
//			else if (line.find("fragment") != std::string::npos)
//				type = ShaderType::FRAGMENT;
//		}
//		else
//		{
//			ss[(int)type] << line << "\n";
//		}
//	}
//
//	return { ss[0].str(),ss[1].str() };
//}

//static unsigned int CompileShader(unsigned int type, const std::string& source)
//{
//	unsigned int id;
//	GLCall(id = glCreateShader(type));
//	const char* src = source.c_str();
//	GLCall(glShaderSource(id, 1, &src, nullptr));
//	GLCall(glCompileShader(id));
//	//TODO: ERROR handing
//
//	int result;
//	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
//	if (result == GL_FALSE) {
//		int length;
//		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
//		char* message = (char*)_malloca(length * sizeof(char));
//		GLCall(glGetShaderInfoLog(id, length, &length, message));
//		std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
//		std::cout << message << std::endl;
//		GLCall(glDeleteShader(id));
//		return 0;
//	}
//
//	return id;
//}

//static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//	unsigned int program;
//	GLCall(program = glCreateProgram());
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	GLCall(glAttachShader(program, vs));
//	GLCall(glAttachShader(program, fs));
//	GLCall(glLinkProgram(program));
//	GLCall(glValidateProgram(program));
//
//	GLCall(glDeleteShader(vs));
//	GLCall(glDeleteShader(fs));
//
//	return program;
//}

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
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			-0.5f,0.5f
		};

		float vertex2[] = {
			-0.2f, -0.2f, 0.0f,
			0.8f, -0.2f, 0.0f,
			0.8f, 0.8f, 0.0f,
			-0.2f, 0.8f, 0.0f
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		VertexArray va;
		VertexBuffer vb(vertex, sizeof(float) * 4 * 2);
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		VertexArray va2;
		VertexBuffer vb2(vertex2, sizeof(float) * 6 * 2);
		VertexBufferLayout layout2;
		layout2.Push<float>(3);
		va2.AddBuffer(vb2, layout2);
		//GLCall(glEnableVertexAttribArray(0));
		//GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0));

		IndexBuffer ibo(indices, 6);

		ShaderProgramSource source = ParseShader("res/shader/Basic.shader");
		unsigned int shader = CreateShader(source.VertexShader, source.FragmentShader);
		GLCall(glUseProgram(shader));

		int location;
		GLCall(location = glGetUniformLocation(shader, "u_Color"));
		ASSERT(location != -1);
		GLCall(glUniform4f(location, 0.9f, 0.3f, 0.8f, 1.0f));

		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));//…Ë÷√◊¥Ã¨
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		float r = 0.0f;
		float increment = 0.05f;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			//glDrawArrays(GL_TRIANGLES, 0, 3);//“ª¥Œdrawcall
			GLCall(glUseProgram(shader));
			GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

			if ( r < 0.5f)
			{
				//GLCall(glBindVertexArray(vao));
				va.Bind();
			}
			else
			{
				//GLCall(glBindVertexArray(vao2));
				va2.Bind();
			}
			ibo.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			if (r > 1.0f)
			{
				increment = -0.05f;
			}
			else if (r < 0.0f)
			{
				increment = 0.05f;
			}

			r += increment;

			/* GLClearError();
			 glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr);
			 ASSERT(GLLogCall());*/

			 /* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		GLCall(glDeleteProgram(shader));
	}
	glfwTerminate();
	return 0;
}