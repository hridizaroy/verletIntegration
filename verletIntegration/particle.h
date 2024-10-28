#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:
	sf::Vector2f pos;
	sf::Vector2f prevPos;
	sf::Vector2f acceleration;
	bool isPinned;

	Particle(float x, float y, bool pinned);

	void apply_force(const sf::Vector2f& force);

	void update(float time_step);

	void contrainToBounds(float width, float height, float radius);
};