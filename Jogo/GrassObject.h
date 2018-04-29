/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GRASSOBJECT_H
#define GRASSOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class GrassObject : public GameObject
{
public:
	// Constructor(s)
	GrassObject(glm::vec2 pos, Texture2D sprite);
	// Resets the ball to original state with given position and velocity
	void      Reset(glm::vec2 position);
};

#endif

