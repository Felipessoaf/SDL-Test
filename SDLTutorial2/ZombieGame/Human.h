#pragma once

#include "Agent.h"

class Human : public Agent
{
public:
	using Agent::Agent;

	virtual void UpdateDirection() override;
};