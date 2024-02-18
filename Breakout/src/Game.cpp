#include <iostream>
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "BallObject.h"
#include "ParticleGenerator.h"
#include "PostProcessor.h"
#include "glm/gtc/matrix_transform.hpp"
#include "irrKlang/irrKlang.h"

namespace Breakout {

	// collision detection
	bool CheckCollision(GameObject& one, GameObject& two);
	Collision CheckCollision(BallObject& one, GameObject& two); // AABB - Circle collision
	Direction VectorDirection(glm::vec2 target);
	void ActivatePowerUp(PowerUp& powerUp);

	// Game-related State data
	SpriteRenderer* Renderer;
	GameObject* Player;
	BallObject* Ball; 
	ParticleGenerator* Particles;
	PostProcessor* Effects;
	irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();

	float ShakeTime = 0.0f;

	Game::Game(unsigned int width, unsigned int height)
		: State(GAME_ACTIVE), Keys(), Width(width), Height(height), Level(0), Lives(3)
	{
		
	}

	Game::~Game()
	{
		delete Renderer;
		delete Player;
		delete Ball;
		delete Particles;
		delete Effects;
		SoundEngine->drop();
	}

	void Game::Init()
	{
		// ������ɫ��
		ResourceManager::LoadShader("res/shader/sprite.vs", "res/shader/sprite.fs", nullptr, "sprite");
		ResourceManager::LoadShader("res/shader/particle.vs", "res/shader/particle.fs", nullptr, "particle");
		ResourceManager::LoadShader("res/shader/postProcessing.vs", "res/shader/postProcessing.fs", nullptr, "postprocessing");
		// ������ɫ��
		glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
			static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);

		ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
		ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
		ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
		ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
		// ����ר������Ⱦ�Ŀ���
		Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
		// ��������
		ResourceManager::LoadTexture("res/textures/awesomeface.png", GL_TRUE, "face");
		ResourceManager::LoadTexture("res/textures/particle.png", GL_TRUE, "particle");

		// ��������
		ResourceManager::LoadTexture("res/textures/background.jpg", GL_FALSE, "background");
		ResourceManager::LoadTexture("res/textures/awesomeface.png", GL_TRUE, "face");
		ResourceManager::LoadTexture("res/textures/block.png", GL_FALSE, "block");
		ResourceManager::LoadTexture("res/textures/block_solid.png", GL_FALSE, "block_solid");

		ResourceManager::LoadTexture("res/textures/paddle.png", true, "paddle");

		ResourceManager::LoadTexture("res/textures/powerup_speed.png", true, "powerup_speed");
		ResourceManager::LoadTexture("res/textures/powerup_sticky.png", true, "powerup_sticky");
		ResourceManager::LoadTexture("res/textures/powerup_increase.png", true, "powerup_increase");
		ResourceManager::LoadTexture("res/textures/powerup_confuse.png", true, "powerup_confuse");
		ResourceManager::LoadTexture("res/textures/powerup_chaos.png", true, "powerup_chaos");
		ResourceManager::LoadTexture("res/textures/powerup_passthrough.png", true, "powerup_passthrough");
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

		Particles = new ParticleGenerator(ResourceManager::GetShader("particle"),ResourceManager::GetTexture("particle"), 500);
		Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);
		// audio
		SoundEngine->play2D("res/audio/breakout.mp3", GL_TRUE);
	}

	void Game::Update(float dt)
	{
		Ball->Move(dt, this->Width);
		// �����ײ
		this->DoCollisions();
		// update particles
		Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2.0f));
		// update PowerUps
		this->UpdatePowerUps(dt);

		// reduce shake time
		if (ShakeTime > 0.0f)
		{
			ShakeTime -= dt;
			if (ShakeTime <= 0.0f)
				Effects->Shake = false;
		}

		if (Ball->Position.y >= this->Height) // ���Ƿ�Ӵ��ײ��߽磿
		{
			this->ResetLevel();
			this->ResetPlayer();
		}
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
			Effects->BeginRender();
			// ���Ʊ���
			Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
			// ���ƹؿ�
			this->Levels[this->Level].Draw(*Renderer);
			// draw player
			Player->Draw(*Renderer);

			for (PowerUp& powerUp : this->PowerUps)
				if (!powerUp.Destroyed)
					powerUp.Draw(*Renderer);

			// Draw particles   
			Particles->Draw();
			// draw ball
			Ball->Draw(*Renderer);


			Effects->EndRender();
			Effects->Render(glfwGetTime());
		}
	}

	void ActivatePowerUp(PowerUp& powerUp)
	{
		// ���ݵ������ͷ�������
		if (powerUp.Type == "speed")
		{
			Ball->Velocity *= 1.2;
		}
		else if (powerUp.Type == "sticky")
		{
			Ball->Sticky = GL_TRUE;
			Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
		}
		else if (powerUp.Type == "pass-through")
		{
			Ball->PassThrough = GL_TRUE;
			Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
		}
		else if (powerUp.Type == "pad-size-increase")
		{
			Player->Size.x += 50;
		}
		else if (powerUp.Type == "confuse")
		{
			if (!Effects->Chaos)
				Effects->Confuse = GL_TRUE; // ֻ��chaosδ����ʱ��Ч��chaosͬ��
		}
		else if (powerUp.Type == "chaos")
		{
			if (!Effects->Confuse)
				Effects->Chaos = GL_TRUE;
		}
	}

	void Game::DoCollisions()
	{
		for (GameObject& box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed)
			{
				Collision collision = CheckCollision(*Ball, box);
				if (std::get<0>(collision)) // ���collision �� true
				{
					// ���ש�鲻��ʵ�ľ�����ש��
					if (!box.IsSolid)
					{
						box.Destroyed = GL_TRUE;
						this->SpawnPowerUps(box);
					}
					else
					{
						// �����ʵ�ĵ�ש���򼤻�shake��Ч
						ShakeTime = 0.05f;
						Effects->Shake = true;
					}
					SoundEngine->play2D("res/audio/bleep.mp3", false);

					// ��ײ����
					Direction dir = std::get<1>(collision);
					glm::vec2 diff_vector = std::get<2>(collision);

					if (!(Ball->PassThrough && !box.IsSolid)) // don't do collision resolution on non-solid bricks if pass-through is activated
					{
						if (dir == LEFT || dir == RIGHT) // ˮƽ������ײ
						{
							Ball->Velocity.x = -Ball->Velocity.x; // ��תˮƽ�ٶ�
							// �ض�λ
							GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
							if (dir == LEFT)
								Ball->Position.x += penetration; // ��������
							else
								Ball->Position.x -= penetration; // ��������
						}
						else // ��ֱ������ײ
						{
							Ball->Velocity.y = -Ball->Velocity.y; // ��ת��ֱ�ٶ�
							// �ض�λ
							GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
							if (dir == UP)
								Ball->Position.y -= penetration; // ��������
							else
								Ball->Position.y += penetration; // ��������
						}
					}
				}
			}
		}

		for (PowerUp& powerUp : this->PowerUps)
		{
			if (!powerUp.Destroyed)
			{
				if (powerUp.Position.y >= this->Height)
					powerUp.Destroyed = GL_TRUE;
				if (CheckCollision(*Player, powerUp))
				{   // �����뵲��Ӵ�����������
					ActivatePowerUp(powerUp);
					powerUp.Destroyed = GL_TRUE;
					powerUp.Activated = GL_TRUE;
					SoundEngine->play2D("res/audio/powerup.wav", false);
				}
			}
		}

		Collision result = CheckCollision(*Ball, *Player);
		if (!Ball->Stuck && std::get<0>(result))
		{
			// ��������˵�����ĸ�λ�ã������������ĸ�λ�����ı��ٶ�
			float centerBoard = Player->Position.x + Player->Size.x / 2;
			float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
			float percentage = distance / (Player->Size.x / 2);
			// ���ݽ���ƶ�
			float strength = 2.0f;
			glm::vec2 oldVelocity = Ball->Velocity;
			Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
			//Ball->Velocity.y = -Ball->Velocity.y;
			Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
			Ball->Velocity.y = -1 * abs(Ball->Velocity.y);

			// if Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculated
			Ball->Stuck = Ball->Sticky;

			SoundEngine->play2D("res/audio/bleep.wav", false);

		}
	}

	void Game::ResetLevel()
	{
		if (this->Level == 0)
			this->Levels[0].Load("levels/one.lvl", this->Width, this->Height / 2);
		else if (this->Level == 1)
			this->Levels[1].Load("levels/two.lvl", this->Width, this->Height / 2);
		else if (this->Level == 2)
			this->Levels[2].Load("levels/three.lvl", this->Width, this->Height / 2);
		else if (this->Level == 3)
			this->Levels[3].Load("levels/four.lvl", this->Width, this->Height / 2);

		this->Lives = 3;
	}

	void Game::ResetPlayer()
	{
		// reset player/ball stats
		Player->Size = PLAYER_SIZE;
		Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
		Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
		// also disable all active powerups
		/*Effects->Chaos = Effects->Confuse = false;
		Ball->PassThrough = Ball->Sticky = false;*/
		Player->Color = glm::vec3(1.0f);
		Ball->Color = glm::vec3(1.0f);
	}

	bool ShouldSpawn(GLuint chance)
	{
		GLuint random = rand() % chance;
		return random == 0;
	}

	void Game::SpawnPowerUps(GameObject& block)
	{
		if (ShouldSpawn(75)) // 1/75�ļ���
			this->PowerUps.push_back(
				PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")
				));
		if (ShouldSpawn(75))
			this->PowerUps.push_back(
				PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")
				));
		if (ShouldSpawn(75))
			this->PowerUps.push_back(
				PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")
				));
		if (ShouldSpawn(75))
			this->PowerUps.push_back(
				PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")
				));
		if (ShouldSpawn(15)) // ������߱���Ƶ��������
			this->PowerUps.push_back(
				PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")
				));
		if (ShouldSpawn(15))
			this->PowerUps.push_back(
				PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")
				));
	}

	bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
	{
		// Check if another PowerUp of the same type is still active
		// in which case we don't disable its effect (yet)
		for (const PowerUp& powerUp : powerUps)
		{
			if (powerUp.Activated)
				if (powerUp.Type == type)
					return true;
		}
		return false;
	}

	void Game::UpdatePowerUps(GLfloat dt)
	{
		for (PowerUp& powerUp : this->PowerUps)
		{
			powerUp.Position += powerUp.Velocity * dt;
			if (powerUp.Activated)
			{
				powerUp.Duration -= dt;

				if (powerUp.Duration <= 0.0f)
				{
					// ֮��Ὣ��������Ƴ�
					powerUp.Activated = GL_FALSE;
					// ͣ��Ч��
					if (powerUp.Type == "sticky")
					{
						if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
						{   // ����û������stickyЧ�����ڼ���״̬ʱ���ã�����ͬ��
							Ball->Sticky = GL_FALSE;
							Player->Color = glm::vec3(1.0f);
						}
					}
					else if (powerUp.Type == "pass-through")
					{
						if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
						{
							Ball->PassThrough = GL_FALSE;
							Ball->Color = glm::vec3(1.0f);
						}
					}
					else if (powerUp.Type == "confuse")
					{
						if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
						{
							Effects->Confuse = GL_FALSE;
						}
					}
					else if (powerUp.Type == "chaos")
					{
						if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
						{
							Effects->Chaos = GL_FALSE;
						}
					}
				}
			}
		}

		this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
			[](const PowerUp& powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
		), this->PowerUps.end());
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

	Collision CheckCollision(BallObject& one, GameObject& two) // AABB - Circle collision
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
		//return glm::length(difference) < one.Radius;
		if (glm::length(difference) <= one.Radius)
			return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
		else
			return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
	}

	Direction VectorDirection(glm::vec2 target)
	{
		glm::vec2 compass[] = {
			glm::vec2(0.0f, 1.0f),  // ��
			glm::vec2(1.0f, 0.0f),  // ��
			glm::vec2(0.0f, -1.0f), // ��
			glm::vec2(-1.0f, 0.0f)  // ��
		};
		GLfloat max = 0.0f;
		GLuint best_match = -1;
		for (GLuint i = 0; i < 4; i++)
		{
			GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
			if (dot_product > max)
			{
				max = dot_product;
				best_match = i;
			}
		}
		return (Direction)best_match;
	}
}