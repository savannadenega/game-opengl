

/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "GridObject.h"

GridObject::GridObject()
	: GameObject(), Stuck(true) { }

GridObject::GridObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos,                 //posicao
		size,                         //size
		sprite,                       //sprite
		glm::vec3(1.0f),              //color
		glm::vec2(0.2f, 0.0f)),       //velocity
	Stuck(true) { }

void GridObject::Move(GridObject *grid)
{

	if (!grid->Stuck) {
		grid->Position.x -= grid->Velocity.x;

		if (grid->Position.x <= -65.0f) {
			grid->Position.x = 1280.0f;
		}

	}
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void GridObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
}

