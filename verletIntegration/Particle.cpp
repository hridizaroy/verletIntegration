#include "Particle.h"


Particle::Particle(float x, float y, bool pinned) :
	pos(x, y), prevPos(x, y), acceleration(0, 0), isPinned(pinned)
{

}

void Particle::apply_force(const sf::Vector2f& force)
{
	if (!isPinned)
	{
		acceleration += force;
	}	
}

void Particle::update(float time_step)
{
	if (!isPinned)
	{
		sf::Vector2f prevDist = pos - prevPos;
		prevPos = pos;

		pos += prevDist + acceleration * time_step * time_step;

		acceleration = sf::Vector2f(0, 0); // reset
	}
}

void Particle::contrainToBounds(float width, float height)
{
	pos.x = std::min(width, std::max(0.0f, pos.x));
	pos.y = std::min(height, std::max(0.0f, pos.y));
}