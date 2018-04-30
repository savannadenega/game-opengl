

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "GameObject.h"
#include "Texture2D.h"
#include "SpriteRenderer.h"

GameObject::GameObject()
	: Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Displayed(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Displayed(false) { }

void GameObject::Draw(SpriteRenderer &renderer, GLfloat z)
{
	renderer.DrawSprite(this->Sprite, this->Position, z, this->Size, this->Rotation, this->Color);
}

void GameObject::DrawPlayer(SpriteRenderer &renderer, GLfloat z)
{
	renderer.DrawSpritePlayer(this->Sprite, this->Position, z, this->Size, this->Rotation, this->Color);
}

