#pragma once

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class CollisionEvent: public Event
{
public:
	CollisionEvent(Entity a, Entity b) : a(a), b(b) {}

	Entity a;
	Entity b;
};