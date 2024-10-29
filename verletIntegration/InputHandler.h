#pragma once

#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "Constraint.h"

class InputHandler
{
public:
	// Maximum distance from mouse click to any constraint
	static inline const float CLICK_TOLERANCE = 5.0f;

	static void handleMouseClick(const sf::Event& event,
		std::vector<Particle>& particles, std::vector<Constraint>& constraints);

private:
	static float pointToConstraintDist(float x, float y, const Constraint& constraint);

	static Constraint* findNearestConstraint(float mouse_x, float mouse_y,
		const std::vector<Constraint>& constraints);

	static void tearCloth(float mouse_x, float mouse_y,
		const std::vector<Particle>& particles, std::vector<Constraint>& constraints);
};