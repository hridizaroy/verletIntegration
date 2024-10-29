#include "Constraint.h"

Constraint::Constraint(Particle* p1, Particle* p2):
						p1(p1), p2(p2)
{
	initial_length = std::hypot(p2->pos.x - p1->pos.x,
						p2->pos.y - p1->pos.y);
	
	active = true;
}

void Constraint::satisfy()
{
	if (!active)
	{
		return;
	}

	sf::Vector2f delta = p2->pos - p1->pos;

	float curr_length = std::hypot(delta.x, delta.y);
	float diff = (curr_length - initial_length) / curr_length;

	sf::Vector2f correction = delta * 0.5f * diff;

	if (!p1->isPinned)
	{
		p1->pos += correction;
	}
	
	if (!p2->isPinned)
	{
		p2->pos -= correction;
	}
}

void Constraint::deactivate()
{
	active = false;
}