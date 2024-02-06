#pragma once
#include "GLFW/glfw3.h"
#include <vector>
#include "GameLevel.h"

namespace Breakout {
	enum GameState
	{
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};

	// Represents the four possible (collision) directions
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	// Defines a Collision typedef that represents collision data
	typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

	// Initial size of the player paddle
	const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
	// Initial velocity of the player paddle
	const float PLAYER_VELOCITY(500.0f);
	// Initial velocity of the Ball
	const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
	// ÇòµÄ°ë¾¶
	const GLfloat BALL_RADIUS = 12.5f;

	class Game
	{
	public:
		GameState State;

		bool Keys[1024];
		unsigned int Width, Height;

		std::vector<GameLevel>  Levels;
		unsigned int            Level;	

		Game(unsigned int width, unsigned int height);
		~Game();

		void Init();
		void ProcessInput(float dt);
		void Update(float dt);
		void Render();
		void DoCollisions();
	};
}
