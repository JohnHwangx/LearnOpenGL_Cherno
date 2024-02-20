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

        // configure instanced array
        // -------------------------
        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, m_Amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

        // set transformation matrices as an instance vertex attribute (with divisor 1)
        // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
        // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
        // -----------------------------------------------------------------------------------------------------------------------------------
        for (unsigned int i = 0; i < m_Rock->meshes.size(); i++)
        {
            unsigned int VAO = m_Rock->meshes[i]->GetVAO();
            glBindVertexArray(VAO);
            // set attribute pointers for matrix (4 times vec4)
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glBindVertexArray(0);
        }
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
        m_AsteroidShader->SetUniform1i("texture_diffuse1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Rock->textures_loaded[0]->GetRendererId()); // note: we also made the textures_loaded vector public (instead of private) from the model class.
        for (unsigned int i = 0; i < m_Rock->meshes.size(); i++)
        {
            glBindVertexArray(m_Rock->meshes[i]->GetVAO());
            glDrawElementsInstanced(GL_TRIANGLES, m_Rock->meshes[i]->indices.size(), GL_UNSIGNED_INT, 0, m_Amount);
            glBindVertexArray(0);
        }
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