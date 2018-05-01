/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "PlayerObject.h"

PlayerObject::PlayerObject()
	: GameObject(), Stuck(true) { }

PlayerObject::PlayerObject(glm::vec2 pos, Texture2D sprite)
	: GameObject(pos,                   //posicao
		glm::vec2(58, 100),             //size
		sprite,                         //sprite
		glm::vec3(1.0f),                //color
		glm::vec2(0.0f, 0.0f)),         //velocity
	Stuck(true) { }

glm::vec2 PlayerObject::Move(GLfloat dt, GLuint window_width)
{
	// If not stuck to player board
	if (!this->Stuck)
	{
		// Move the ball
		this->Position += this->Velocity * dt;
		// Then check if outside window bounds and if so, reverse velocity and restore at correct position
		if (this->Position.x <= 0.0f)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = 0.0f;
		}
		else if (this->Position.x + this->Size.x >= window_width)
		{
			this->Velocity.x = -this->Velocity.x;
			this->Position.x = window_width - this->Size.x;
		}
		if (this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}
	}
	return this->Position;
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void PlayerObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
}

void PlayerObject::Jump(GLfloat velocity)
{
		FramesDoPulo++;

		if (Position.y > 0)
			Position.y -= 1.0f;

		if (FramesDoPulo == 6) {
			FramesDoPulo = 0;
			ControleMovimento = 0;
		}
}

