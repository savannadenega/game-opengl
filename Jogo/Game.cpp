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

BackgroundObject *Background1;
BackgroundObject *Background2;
PlayerObject    *Player;
GrassObject     *Grass1;
GrassObject     *Grass2;

GridObject      *Grid1A;
GridObject      *Grid1B;
GridObject      *Grid2A;
GridObject      *Grid2B;
GridObject      *Grid3A;
GridObject      *Grid3B;
GridObject      *Grid4A;
GridObject      *Grid4B;
GridObject      *Grid5A;
GridObject      *Grid5B;

GameObject      *GameOver;


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
	//ResourceManager::LoadShader("shaders/sprite.vs", "shaders/player.frag", nullptr, "spritePlayer");

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
	
	ResourceManager::LoadTexture("textures/Lulinha.png", GL_TRUE, "Lulinha");
	ResourceManager::LoadTexture("textures/GameOver.jpg", GL_TRUE, "GameOver");

	// Set render-specific controls
	Shader shader1 = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader1);

	//Player
	glm::vec2 playerPos = glm::vec2(200, 300);
	Player = new PlayerObject(playerPos, ResourceManager::GetTexture("Lulinha"), glm::vec2(1.0f/3.0f, 0.0f));
	//Player = new PlayerObject(playerPos, ResourceManager::GetTexture("Lulinha"));

	//Background1
	glm::vec2 GameOverPos = glm::vec2(1280, 0);
	GameOver = new GameObject(GameOverPos, glm::vec2(this->Width, this->Height), ResourceManager::GetTexture("GameOver"));

	//Background1
	glm::vec2 background1Pos = glm::vec2(0, 0);
	Background1 = new BackgroundObject(background1Pos, glm::vec2(1280, this->Height), ResourceManager::GetTexture("background"));
	//Background2
	glm::vec2 background2Pos = glm::vec2(1280, 0);
	Background2 = new BackgroundObject(background2Pos, glm::vec2((this->Width), (this->Height)), ResourceManager::GetTexture("background"));

	//Grass1
	glm::vec2 grass1Pos = glm::vec2(0, 636);
	Grass1 = new GrassObject(grass1Pos, ResourceManager::GetTexture("grass"));
	//Grass2
	glm::vec2 grass2Pos = glm::vec2(1280, 636);
	Grass2 = new GrassObject(grass2Pos, ResourceManager::GetTexture("grass"));

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

	//Grid4A
	glm::vec2 Grid4APos = glm::vec2(((this->Width / 5) * 5), 0);
	Grid4A = new GridObject(Grid4APos, glm::vec2(65, 275), ResourceManager::GetTexture("grid-GrandeCima"));
	//Grid4B
	glm::vec2 Grid4BPos = glm::vec2(((this->Width / 5) * 5), 513);
	Grid4B = new GridObject(Grid4BPos, glm::vec2(65, 207), ResourceManager::GetTexture("grid-PequenaBaixo"));

	//Grid5A
	glm::vec2 Grid5APos = glm::vec2(((this->Width / 5) * 6) - 32.5, 0);
	Grid5A = new GridObject(Grid5APos, glm::vec2(65, 207), ResourceManager::GetTexture("grid-PequenaCima"));
	//Grid5B
	glm::vec2 Grid5BPos = glm::vec2(((this->Width / 5) * 6) - 32.5, 445);
	Grid5B = new GridObject(Grid5BPos, glm::vec2(65, 275), ResourceManager::GetTexture("grid-GrandeBaixo"));

}

void Game::Update(GLfloat dt)
{

	Background1->Move(Background1);
	Background2->Move(Background2);

	Grass1->Move(Grass1);
	Grass2->Move(Grass2);
	
	Grid1A->Move(Grid1A);
	Grid1B->Move(Grid1B);
	Grid2A->Move(Grid2A);
	Grid2B->Move(Grid2B);
	Grid3A->Move(Grid3A);
	Grid3B->Move(Grid3B);
	Grid4A->Move(Grid4A);
	Grid4B->Move(Grid4B);
	Grid5A->Move(Grid5A);
	Grid5B->Move(Grid5B);

	if (GameOver->Displayed){
		GameOver->Position.x = 1280.0f;
	}

	// Check for collisions
	this->DoCollisions();
}

void Game::ProcessInput(GLfloat dt)
{
	//Reset
	if (this->Keys[GLFW_KEY_BACKSPACE] and this->State == GAME_OVER) {
		this->Init();
		this->State = GAME_ACTIVE;
	}

	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		// Move playerboard

		if (this->Keys[GLFW_KEY_SPACE]) {
			
			Player->Stuck = false;
			Background1->Stuck = false;
			Background2->Stuck = false;
			Grass1->Stuck = false;
			Grass2->Stuck = false;
			Grid1A->Stuck = false;
			Grid1B->Stuck = false;
			Grid2A->Stuck = false;
			Grid2B->Stuck = false;
			Grid3A->Stuck = false;
			Grid3B->Stuck = false;
			Grid4A->Stuck = false;
			Grid4B->Stuck = false;
			Grid5A->Stuck = false;
			Grid5B->Stuck = false;

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
					Player->Position.y += 0.8f;
				}
				if (Player->TexturePosX >= 0.0f)
					Player->TexturePosX -= 1.0f / 3.0f;
			}
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE || this->State == GAME_OVER)
	{
		// Draw background
		//Texture2D texture2 = ResourceManager::GetTexture("background");
		//Renderer->DrawSprite(texture2, glm::vec2(0, 0), 0.1f, glm::vec2(this->Width, this->Height), 0.0f);

		Shader shader1 = ResourceManager::GetShader("sprite");
		RendererPlayer = new SpriteRenderer(shader1, Player->TexturePosX - 1.0f/3.0f, Player->TexturePosX);

		//Shader shader1 = ResourceManager::GetShader("spritePlayer");
		//RendererPlayer = new SpriteRenderer(shader1, Player->TexturePosX - 1.0f / 3.0f, Player->TexturePosX);
		

		Background1->Draw(*Renderer, 0.1f);
		Background2->Draw(*Renderer, 0.1f);

		Player->DrawPlayer(*RendererPlayer, 0.2f);
		//Player->Draw(*Renderer, 0.02f);

		Grid1A->Draw(*Renderer, 0.02f);
		Grid1B->Draw(*Renderer, 0.02f);

		Grid2A->Draw(*Renderer, 0.02f);
		Grid2B->Draw(*Renderer, 0.02f);

		Grid3A->Draw(*Renderer, 0.02f);
		Grid3B->Draw(*Renderer, 0.02f);

		Grid4A->Draw(*Renderer, 0.02f);
		Grid4B->Draw(*Renderer, 0.02f);

		Grid5A->Draw(*Renderer, 0.02f);
		Grid5B->Draw(*Renderer, 0.02f);

		Grass1->Draw(*Renderer, 0.02f);
		Grass2->Draw(*Renderer, 0.02f);

		GameOver->Draw(*Renderer, 0.02f);

	}
}


void Game::DoCollisions()
{

	if (CheckCollision(*Player, *Grass1))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}

	if (CheckCollision(*Player, *Grass2))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grass2))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}

	if (CheckCollision(*Player, *Grid1A))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid1B))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid2A))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid2B))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid3A))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid3B))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid4A))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid4B))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid5A))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}
	if (CheckCollision(*Player, *Grid5B))
	{
		GameOver->Position.x = 0.0f;
		this->State = GAME_OVER;
	}

}

GLboolean Game::CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
	// Collision x-axis?
	GLboolean collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	GLboolean collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}



