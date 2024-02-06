#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "BallObject.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Breakout {

	// collision detection
	bool CheckCollision(GameObject& one, GameObject& two);
	bool CheckCollision(BallObject& one, GameObject& two); // AABB - Circle collision

	// Game-related State data
	SpriteRenderer* Renderer;
	GameObject* Player;
	BallObject* Ball;

	Game::Game(unsigned int width, unsigned int height)
		: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
	{
		
	}

	Game::~Game()
	{

	}

	void Game::Init()
	{
		// ������ɫ��
		ResourceManager::LoadShader("res/shader/sprite.vs", "res/shader/sprite.fs", nullptr, "sprite");
		// ������ɫ��
		glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
			static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

		ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
		ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
		// ����ר������Ⱦ�Ŀ���
		Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
		// ��������
		ResourceManager::LoadTexture("res/textures/awesomeface.png", GL_TRUE, "face");

		// ��������
		ResourceManager::LoadTexture("res/textures/background.jpg", GL_FALSE, "background");
		ResourceManager::LoadTexture("res/textures/awesomeface.png", GL_TRUE, "face");
		ResourceManager::LoadTexture("res/textures/block.png", GL_FALSE, "block");
		ResourceManager::LoadTexture("res/textures/block_solid.png", GL_FALSE, "block_solid");

		ResourceManager::LoadTexture("res/textures/paddle.png", true, "paddle");
		// ���عؿ�
		GameLevel one; one.Load("res/levels/one.lvl", this->Width, this->Height * 0.5);
		GameLevel two; two.Load("res/levels/two.lvl", this->Width, this->Height * 0.5);
		GameLevel three; three.Load("res/levels/three.lvl", this->Width, this->Height * 0.5);
		GameLevel four; four.Load("res/levels/four.lvl", this->Width, this->Height * 0.5);
		this->Levels.push_back(one);
		this->Levels.push_back(two);
		this->Levels.push_back(three);
		this->Levels.push_back(four);
		this->Level = 1;

		glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
		Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

		glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
		Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
	}

	void Game::Update(float dt)
	{
		Ball->Move(dt, this->Width);
		// �����ײ
		this->DoCollisions();
	}


	void Game::ProcessInput(float dt)
	{
		if (this->State == GAME_ACTIVE)
		{
			float velocity = PLAYER_VELOCITY * dt;
			// �ƶ�����
			if (this->Keys[GLFW_KEY_A])
			{
				if (Player->Position.x >= 0) {
					Player->Position.x -= velocity;
					if (Ball->Stuck)
						Ball->Position.x -= velocity;
				}
			}
			if (this->Keys[GLFW_KEY_D])
			{
				if (Player->Position.x <= this->Width - Player->Size.x)
				{
					Player->Position.x += velocity;
					if (Ball->Stuck)
						Ball->Position.x += velocity;
				}
			}
			if (this->Keys[GLFW_KEY_SPACE])
				Ball->Stuck = false;
		}
	}

	void Game::Render()
	{
		//Renderer->DrawSprite(ResourceManager::GetTexture("face"),
			//glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		if (this->State == GAME_ACTIVE)
		{
			// ���Ʊ���
			Renderer->DrawSprite(ResourceManager::GetTexture("background"),
				glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
			);
			// ���ƹؿ�
			this->Levels[this->Level].Draw(*Renderer);
			// draw player
			Player->Draw(*Renderer);

			// draw ball
			Ball->Draw(*Renderer);
		}
	}

	void Game::DoCollisions()
	{
		for (GameObject& box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed)
			{
				if (CheckCollision(*Ball, box))
				{
					if (!box.IsSolid)
						box.Destroyed = GL_TRUE;
				}
			}
		}
	}

	bool CheckCollision(GameObject& one, GameObject& two) // AABB - AABB collision
	{
		// x�᷽����ײ��
		bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
			two.Position.x + two.Size.x >= one.Position.x;
		// y�᷽����ײ��
		bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
			two.Position.y + two.Size.y >= one.Position.y;
		// ֻ��������������ײʱ����ײ
		return collisionX && collisionY;
	}

	bool CheckCollision(BallObject& one, GameObject& two) // AABB - Circle collision
	{
		// ��ȡԲ������ 
		glm::vec2 center(one.Position + one.Radius);
		// ����AABB����Ϣ�����ġ���߳���
		glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
		glm::vec2 aabb_center(
			two.Position.x + aabb_half_extents.x,
			two.Position.y + aabb_half_extents.y
		);
		// ��ȡ�������ĵĲ�ʸ��
		glm::vec2 difference = center - aabb_center;
		glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		// AABB_center����clamped�����͵õ�����ײ���Ͼ���Բ����ĵ�closest
		glm::vec2 closest = aabb_center + clamped;
		// ���Բ��center�������closest��ʸ�����ж��Ƿ� length <= radius
		difference = closest - center;
		return glm::length(difference) < one.Radius;
	}
}