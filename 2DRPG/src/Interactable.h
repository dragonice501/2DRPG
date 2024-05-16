#pragma once

#include "GameObject.h"

#include "Vec2.h"

class Interactable : public GameObject
{
private:
	Vec2 mPosition;

public:
	const Vec2& GetPosition() const { return mPosition; }

	void SetPosition(const Vec2& position) { mPosition = position; }
};