#include "16_AsteroidsInstanced.h"
#include "glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>
#include "imgui/imgui.h"
#include <GLFW/glfw3.h>

namespace Test {

	Part4_AsteroidInstanced::Part4_AsteroidInstanced()
        :m_Amount(10000)
	{
        m_Distance = 300.0f;
        m_Camera->SetDistance(m_Distance);

		m_AsteroidShader = std::make_unique<Shader>("res/shader/Part4_InstancedAsteroid.shader");
		m_PlanetShader = std::make_unique<Shader>("res/shader/Part4_InstancedPlanet.shader");

		m_Rock = std::make_unique<Model>("res/models/rock/rock.obj");
        m_Rock->BindShader(*(m_AsteroidShader.get()));
		m_Planet = std::make_unique<Model>("res/models/planet/planet.obj");
        m_Planet->BindShader(*(m_PlanetShader.get()));

        // generate a large list of semi-random model transformation matrices
        // ------------------------------------------------------------------
        //unsigned int amount = 100000;
        glm::mat4* modelMatrices;
        modelMatrices = new glm::mat4[m_Amount];
        srand(glfwGetTime()); // initialize random seed	
        float radius = 150.0;
        float offset = 25.0f;
        for (unsigned int i = 0; i < m_Amount; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            // 1. translation: displace along circle with 'radius' in range [-offset, offset]
            float angle = (float)i / (float)m_Amount * 360.0f;
            float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float x = sin(angle) * radius + displacement;
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
            displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
            float z = cos(angle) * radius + displacement;
            model = glm::translate(model, glm::vec3(x, y, z));

            // 2. scale: Scale between 0.05 and 0.25f
            float scale = (rand() % 20) / 100.0f + 0.05;
            model = glm::scale(model, glm::vec3(scale));

            // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
            float rotAngle = (rand() % 360);
            model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

            // 4. now add to list of matrices
            modelMatrices[i] = model;
        }

        m_Rock->SetInstancedMatrix(m_Amount, modelMatrices);
	}

	Part4_AsteroidInstanced::~Part4_AsteroidInstanced()
	{
	}

    void Part4_AsteroidInstanced::OnUpdate(float deltaTime)
    {
        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = m_Camera->GetViewMatrix();
        if (m_IsOthor)
            view = glm::scale(view, glm::vec3(m_Distance));

        glm::mat4 projection(1.0f);
        if (m_IsOthor)
            projection = glm::ortho(-15.0f, 15.0f, -10.0f, 10.0f, -30.0f, 1000.0f);
        else
            projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 1500.0f);

        m_AsteroidShader->Bind();
        m_AsteroidShader->SetUniformMat4f("uView", view);
        m_AsteroidShader->SetUniformMat4f("uProjection", projection);

        m_PlanetShader->Bind();
        m_PlanetShader->SetUniformMat4f("uView", view);
        m_PlanetShader->SetUniformMat4f("uProjection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        m_PlanetShader->SetUniformMat4f("uModel", model);
        m_Planet->Draw();

        // draw meteorites
        m_AsteroidShader->Bind();

        m_Rock->DrawInstanced(m_Amount);
    }

	void Part4_AsteroidInstanced::OnRender()
	{
	}

	void Part4_AsteroidInstanced::OnImGuiRender()
	{
        ImGui::Checkbox("IsOthor", &m_IsOthor);
        if (ImGui::DragFloat("Yaw", &m_Yaw, 1.0f, -180.0f, 180.0f))
        {
            m_Camera->CameraYaw(m_Yaw);
        }

        if (ImGui::DragFloat("Pitch", &m_Pitch, 1.0f, -89.9f, 89.9f))
        {
            m_Camera->CameraPitch(m_Pitch);
        }

        if (ImGui::DragFloat("Distance", &m_Distance, 0.1f, 0.1f, 300.0f))
        {
            m_Camera->SetDistance(m_Distance);
        }
	}
}