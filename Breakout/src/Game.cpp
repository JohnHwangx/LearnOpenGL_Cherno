#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

namespace Breakout {

	// Game-related State data
	SpriteRenderer* Renderer;

	Game::Game(unsigned int width, unsigned int height)
		: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
	{
		// ������ɫ��
		ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
		// ������ɫ��
		glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
			static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

		ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
		ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
		// ����ר������Ⱦ�Ŀ���
		Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
		// ��������
		ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
	}

	Game::~Game()
	{

	}

	void Game::Init()
	{

	}

	void Game::Update(float dt)
	{

	}


	void Game::ProcessInput(float dt)
	{

	}

	void Game::Render()
	{

	}
}