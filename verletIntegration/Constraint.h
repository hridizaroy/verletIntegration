#pragma once

#include "Particle.h"

class Constraint
{
public:
	Particle* p1;
	Particle* p2;

	float initial_length;

	bool active;

	Constraint(Particle* p1, Particle* p2);

	void satisfy();

	void deactivate();
};