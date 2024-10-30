#pragma once

#include "Human.h"

class Player : public Human
{
public:
	using Human::Human;

	void UpdateDirection() override;
};

