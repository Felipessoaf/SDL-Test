#pragma once

#include "Agent.h"

class Zombie : public Agent
{
public:
	using Agent::Agent;

	void UpdateDirection() override;
};