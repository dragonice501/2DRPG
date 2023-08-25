#pragma once

#include "../Utils/Vec2.h"

class Actor
{
public:
	Actor() : Actor(Vec2(0.0f)) {}
	Actor(Vec2 position = Vec2(0.0f))
	{
		this->position = position;
	}
	~Actor() {}

	Vec2 position;

private:

};