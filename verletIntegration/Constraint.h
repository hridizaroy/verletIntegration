#pragma once

#include "Particle.h"

class Constraint
{
public:
	Particle* p1;
	Particle* p2;

	float initial_length;

	Constraint(Particle* p1, Particle* p2);

	void satisfy();
};