#pragma once

#include <iostream>

struct Vector2f
{
	Vector2f() : x(0.0f), y(0.0f) {}
	Vector2f(float x, float y) : x(x), y(y) {}

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	float x, y;
};