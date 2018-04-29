/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "GrassObject.h"

GrassObject::GrassObject(glm::vec2 pos, Texture2D sprite)
	: GameObject(pos,                         //posicao
		glm::vec2(1280, 84),                  //size
		sprite,                               //sprite
		glm::vec3(1.0f),                      //color
		glm::vec2(0.0f, 0.0f)) { }            //velocity

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void GrassObject::Reset(glm::vec2 position)
{
	this->Position = position;
}

