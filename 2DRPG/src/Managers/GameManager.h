#pragma once

#include "../Utils/Vec2.h"

class GameManager
{
public:
	inline static const Vec2& GetExitVelocity() { return mExitVelocity; }
	inline static void SetExitVelocity(const Vec2& velocity) { mExitVelocity = velocity; }

private:
	static Vec2 mExitVelocity;
};