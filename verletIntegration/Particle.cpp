#include "Particle.h"


Particle::Particle(float x, float y) :
	pos(x, y), prevPos(x, y), acceleration(0, 0)
{

}

void Particle::apply_force(const sf::Vector2f& force)
{
	acceleration += force;
}

void Particle::update(float time_step)
{
	sf::Vector2f prevDist = pos - prevPos;
	prevPos = pos;

	pos += prevDist + acceleration * time_step * time_step;

	acceleration = sf::Vector2f(0, 0); // reset
}