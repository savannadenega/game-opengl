/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "BallObject.h"
#include "GrassObject.h"
#include "PlayerObject.h"
#include "GridObject.h"
#include "BackgroundObject.h"

// Game-related State data
SpriteRenderer  *Renderer;
SpriteRenderer  *RendererPlayer;

BackgroundObject *Background;
PlayerObject    *Player;
BallObject      *Ball;
GrassObject     *Grass;

GridObject      *Grid1A;
GridObject      *Grid1B;
GridObject      *Grid2A;
GridObject      *Grid2B;
GridObject      *Grid3A;
GridObject      *Grid3B;

GridObject      *Grid4A;
GridObject      *Grid4B;


// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const GLfloat BALL_RADIUS = 12.5f;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/player.frag", nullptr, "spritePlayer");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("textures/background.jpg", GL_TRUE, "background");
	ResourceManager::LoadTexture("textures/grass.png", GL_TRUE, "grass");
	ResourceManager::LoadTexture("textures/GradePequenaCima.png", GL_TRUE, "grid-PequenaCima"); //A
	ResourceManager::LoadTexture("textures/GradeGrandeBaixo.png", GL_TRUE, "grid-GrandeBaixo"); //A

	ResourceManager::LoadTexture("textures/GradeGrandeCima.png", GL_TRUE, "grid-GrandeCima"); //B
	ResourceManager::LoadTexture("textures/GradePequenaBaixo.png", GL_TRUE, "grid-PequenaBaixo"); //B

	ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("textures/block.png", GL_TRUE, "block");
	ResourceManager::LoadTexture("textures/block_solid.png", GL_TRUE, "block_solid");

	ResourceManager::LoadTexture("textures/Lulinha.png", GL_TRUE, "Lulinha");

	// Set render-specific controls
	Shader shader1 = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader1);
	// Load levels
	GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
	GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
	GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
	GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	//Ball
	//glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	//Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
	//	ResourceManager::GetTexture("face"));

	//Player
	//glm::vec2 playerPos = glm::vec2(0.0f + PLAYER_SIZE.x / 2, this->Height / 2);
	glm::vec2 playerPos = glm::vec2(this->Width / 8, 200);
	Player = new PlayerObject(playerPos, ResourceManager::GetTexture("Lulinha"), glm::vec2(1.0f/3.0f, 0.0f));

	//Background
	glm::vec2 BackgroundPos = glm::vec2(0, 0);
	Background = new BackgroundObject(BackgroundPos, glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("background"));

	//Grass
	glm::vec2 grassPos = glm::vec2(0, 636);
	Grass = new GrassObject(grassPos, ResourceManager::GetTexture("grass"));

	//Grid1A
	glm::vec2 grid1APos = glm::vec2(((this->Width / 5) * 2) - 32.5, 0);
	Grid1A = new GridObject(grid1APos, glm::vec2(65, 207), ResourceManager::GetTexture("grid-PequenaCima"));
	//Grid1B
	glm::vec2 Grid1BPos = glm::vec2(((this->Width / 5) * 2) - 32.5, 445);
	Grid1B = new GridObject(Grid1BPos, glm::vec2(65, 275), ResourceManager::GetTexture("grid-GrandeBaixo"));

	//Grid2A
	glm::vec2 Grid2APos = glm::vec2(((this->Width / 5) * 3) - 32.5, 0);
	Grid2A = new GridObject(Grid2APos, glm::vec2(65, 275), ResourceManager::GetTexture("grid-GrandeCima"));
	//Grid2B
	glm::vec2 Grid2BPos = glm::vec2(((this->Width / 5) * 3) - 32.5, 513);
	Grid2B = new GridObject(Grid2BPos, glm::vec2(65, 207), ResourceManager::GetTexture("grid-PequenaBaixo"));

	//Grid3A
	glm::vec2 Grid3APos = glm::vec2(((this->Width / 5) * 4) - 32.5, 0);
	Grid3A = new GridObject(Grid3APos, glm::vec2(65, 207), ResourceManager::GetTexture("grid-PequenaCima"));
	//Grid3B
	glm::vec2 Grid3BPos = glm::vec2(((this->Width / 5) * 4) - 32.5, 445);
	Grid3B = new GridObject(Grid3BPos, glm::vec2(65, 275), ResourceManager::GetTexture("grid-GrandeBaixo"));

}

void Game::Update(GLfloat dt)
{
	// Update objects
	//Ball->Move(dt, this->Width);
	Background->Move(dt, this->Width);

	// Check for collisions
	this->DoCollisions();
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{

		GLfloat velocity = PLAYER_VELOCITY * dt;
		// Move playerboard

		if (this->Keys[GLFW_KEY_SPACE]) {
			Player->Stuck = false;
			Background->Stuck = false;
		}

		if (!Player->Stuck) {
			if (this->Keys[GLFW_KEY_W] or Player->ControleMovimento == 1)
			{
				Player->ControleMovimento = 1;
				Player->Jump(velocity);
				
				if (Player->TexturePosX <= 0.0f)
					Player->TexturePosX += 1.0f / 3.0f;
			}
			else if (this->Keys[GLFW_KEY_S])
			{
				if (Player->Position.y <= this->Width - Player->Size.y)
					Player->Position.y += velocity;
				if(Player->TexturePosX >= 0.0f)
					Player->TexturePosX -= 1.0f/3.0f;
			}else if (Player->ControleMovimento == 0) {
				if (Player->Position.y <= this->Height - Player->Size.y) {
					Player->Position.y += velocity;
				}
				if (Player->TexturePosX >= 0.0f)
					Player->TexturePosX -= 1.0f / 3.0f;
			}
			//Sempre se move para frente
			Player->Position.x += 0.4;
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw background
		//Texture2D texture2 = ResourceManager::GetTexture("background");
		//Renderer->DrawSprite(texture2, glm::vec2(0, 0), 0.1f, glm::vec2(this->Width, this->Height), 0.0f);

		// Draw level
		//this->Levels[this->Level].Draw(*Renderer, 0.00f);
		// Draw player
		// Player->Position = vec2(0.5f,0.5f,);

		Shader shader1 = ResourceManager::GetShader("sprite");
		RendererPlayer = new SpriteRenderer(shader1, Player->TexturePosX - 1.0f/3.0f, Player->TexturePosX);

		//Ball->Draw(*Renderer, 0.2f);

		Background->Draw(*Renderer, 0.2f);
		Player->Draw(*RendererPlayer, 0.2f);
		
		Grid1A->Draw(*Renderer, 0.02f);
		Grid1B->Draw(*Renderer, 0.02f);

		Grid2A->Draw(*Renderer, 0.02f);
		Grid2B->Draw(*Renderer, 0.02f);

		Grid3A->Draw(*Renderer, 0.02f);
		Grid3B->Draw(*Renderer, 0.02f);

		Grass->Draw(*Renderer, 0.02f);
	}
}

GLboolean Game::CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}

void Game::DoCollisions()
{
	for (GameObject &box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			//if (CheckCollision(*Ball, box))
			//{
			//	if (!box.IsSolid)
			//		box.Destroyed = GL_TRUE;
			//}
		}
	}
}



