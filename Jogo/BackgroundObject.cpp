/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
	: GameObject(pos,              //posicao
		size,                      //size
		sprite,                    //sprite
		glm::vec3(1.0f),           //color
		glm::vec2 (0.04f, 0.0f)),   //velocity
	Stuck(true) { }

void BackgroundObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
	this->Stuck = true;
}

void BackgroundObject::Move(BackgroundObject * background)
{
	if (!background->Stuck) {
		background->Position.x -= background->Velocity.x;
		background->Position.x -= background->Velocity.x;

		if (background->Position.x <= -1279.0f) {
			background->Position.x = 1279.0f;
		}
	}
}



