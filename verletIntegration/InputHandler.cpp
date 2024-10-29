#include "InputHandler.h"

void InputHandler::handleMouseClick(const sf::Event& event,
	std::vector<Particle>& particles, std::vector<Constraint>& constraints)
{
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		float mouse_x = static_cast<float>(event.mouseButton.x);
		float mouse_y = static_cast<float>(event.mouseButton.y);
		tearCloth(mouse_x, mouse_y, particles, constraints);
	}
}

float InputHandler::pointToConstraintDist(float x, float y, const Constraint& constraint)
{
	sf::Vector2f point(x, y);
	sf::Vector2f constraintVector = constraint.p2->pos - constraint.p1->pos;
	float constraintLength = std::hypot(constraintVector.x, constraintVector.y);

	// Normalize
	constraintVector = constraintVector / constraintLength;

	sf::Vector2f constraintToPointVector = point - constraint.p1->pos;

	// Dot product
	float projection = constraintVector.x * constraintToPointVector.x +
						constraintVector.y * constraintToPointVector.y;

	float dist;

	if (projection < 0.0f)
	{
		// point lies "beyond" the constraint and closest point is p1
		dist = std::hypot(constraintToPointVector.x, constraintToPointVector.y);
	}
	else if (projection > constraintLength)
	{
		// point lies "beyond" the constraint and closest point is p2
		sf::Vector2f vec = point - constraint.p2->pos;
		dist = std::hypot(vec.x, vec.y);
	}
	else
	{
		// Cross product to get perpendicular distance from point to constraint
		dist = std::abs(constraintVector.x * constraintToPointVector.y -
			constraintVector.y * constraintToPointVector.x);
	}

	return dist;
}

Constraint* InputHandler::findNearestConstraint(float mouse_x, float mouse_y,
									const std::vector<Constraint>& constraints)
{
	Constraint* nearestConstraint = nullptr;
	float minDist = CLICK_TOLERANCE;

	for (const auto& constraint : constraints)
	{
		float dist = pointToConstraintDist(mouse_x, mouse_y, constraint);

		if (dist < minDist)
		{
			minDist = dist;
			nearestConstraint = const_cast<Constraint*>(&constraint);
		}
	}

	return nearestConstraint;
}

void InputHandler::tearCloth(float mouse_x, float mouse_y,
	const std::vector<Particle>& particles, std::vector<Constraint>& constraints)
{
	Constraint* nearest = findNearestConstraint(mouse_x, mouse_y, constraints);

	if (nearest)
	{
		nearest->deactivate();
	}
}
