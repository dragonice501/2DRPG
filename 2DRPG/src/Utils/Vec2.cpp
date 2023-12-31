#include "Vec2.h"
#include <math.h>

Vec2::Vec2(): x(0.0), y(0.0)
{

}

Vec2::Vec2(const float v) : x(v), y(v)
{
}

Vec2::Vec2(const float x, const float y): x(x), y(y)
{

}

void Vec2::Add(const Vec2& v)
{
	x += v.x;
	y += v.y;
}

void Vec2::Sub(const Vec2& v)
{
	x -= v.x;
	y -= v.y;
}

void Vec2::Scale(const float n)
{
	x *= n;
	y *= n;
}

Vec2 Vec2::Rotate(const float angle) const
{
	Vec2 result;
	result.x = x * cos(angle) - y * sin(angle);
	result.y = x * sin(angle) + y * cos(angle);
	return result;
}

float Vec2::Magnitude() const
{
	return sqrtf(x * x + y * y);
}

float Vec2::MagnitudeSquared() const
{
	return (x * x + y * y);
}

Vec2& Vec2::Normalize()
{
	float length = Magnitude();
	if (length != 0.0)
	{
		x /= length;
		y /= length;
	}
    return *this;
}

Vec2 Vec2::UnitVector() const
{
	Vec2 result = Vec2(0, 0);
	float length = Magnitude();
	if (length != 0.0) {
		result.x = x / length;
		result.y = y / length;
	}
    return result;
}

Vec2 Vec2::Normal() const
{
	return Vec2(y, -x).Normalize();
}

float Vec2::Dot(const Vec2& v) const
{
    return (x * v.x) + (y * v.y);
}

float Vec2::Cross(const Vec2& v) const
{
	return (x * v.y) - (y * v.x);
}

float Clamp(float val, float min, float max)
{
	if (val > max) return max;
	else if (val < min) return min;
	else return val;
}

Vec2 Vec2::Lerp(const Vec2& start, const Vec2& end, float rate)
{
	float x = start.x + (end.x - start.x) * rate;
	float y = start.y + (end.y - start.y) * rate;

	if (start.x < end.x)
	{
		x = Clamp(x, start.x, end.x);
	}
	else if (start.x > end.x)
	{
		x = Clamp(x, end.x, start.x);
	}

	if (start.y < end.y)
	{
		y = Clamp(y, start.y, end.y);
	}
	else if (start.y > end.y)
	{
		y = Clamp(y, end.y, start.y);
	}

	return Vec2(x, y);
}

Vec2& Vec2::operator = (const Vec2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

bool Vec2::operator == (const Vec2& v) const
{
	return x == v.x && y == v.y;
}

bool Vec2::operator != (const Vec2& v) const
{
	return !(*this == v);
}

Vec2 Vec2::operator + (const Vec2& v) const
{
	Vec2 result;
	result.x = x + v.x;
	result.y = y + v.y;
	return result;
}

Vec2 Vec2::operator - (const Vec2& v) const
{
	Vec2 result;
	result.x = x - v.x;
	result.y = y - v.y;
	return result;
}

Vec2 Vec2::operator * (const float n) const
{
	Vec2 result;
	result.x = x * n;
	result.y = y * n;
	return result;
}

Vec2 Vec2::operator / (const float n) const
{
	Vec2 result;
	result.x = x / n;
	result.y = y / n;
	return result;
}

Vec2& Vec2::operator += (const Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vec2& Vec2::operator -= (const Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vec2& Vec2::operator *= (const float n)
{
	x *= n;
	y *= n;
    return *this;
}

Vec2& Vec2::operator /= (const float n)
{
	x /= n;
	y /= n;
    return *this;
}

Vec2 Vec2::operator - ()
{
	Vec2 result;
	result.x = x * -1;
	result.y = y * -1;
	return result;
}