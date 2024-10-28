#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:
	sf::Vector2f pos;
	sf::Vector2f prevPos;
	sf::Vector2f acceleration;

	Particle(float x, float y) : pos(x, y), prevPos(x, y),
		acceleration(x, y)
	{

	}

};