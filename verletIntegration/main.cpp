#include <SFML/Graphics.hpp>
#include <vector>

#include "Particle.h"
#include "Constraint.h"

const int WIDTH = 1080;
const int HEIGHT = 720;
const float PARTICLE_RADIUS = 10.0f;
const float GRAVITY = 9.8f;
const float TIME_STEP = 0.1f;

const int ROW = 10;
const int COL = 10;
const int REST_DIST = 30.0f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");
	window.setFramerateLimit(60);

	std::vector<Particle> particles;
	std::vector<Constraint> constraints;

	for (int row = 0; row < ROW; row++)
	{
		for (int col = 0; col < COL; col++)
		{
			float x = col * REST_DIST + WIDTH / 3;
			float y = row * REST_DIST + HEIGHT / 3;
			bool pinned = (row == 0);
			particles.emplace_back(x, y, pinned);
		}
	}

	for (int row = 0; row < ROW; row++)
	{
		for (int col = 0; col < COL; col++)
		{
			// Horizontal constraint
			if (col < COL - 1)
			{
				int idx = row * COL + col;
				constraints.emplace_back(&particles[idx], &particles[idx + 1]);
			}

			// Vertical constraint
			if (row < ROW - 1)
			{
				int idx = row * COL + col;
				constraints.emplace_back(&particles[row * COL + col],
											&particles[(row + 1) * COL + col]);
			}
		}
	}

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// apply gravity
		for (auto& particle : particles)
		{
			particle.apply_force(sf::Vector2f(0, GRAVITY));
			particle.update(TIME_STEP);
			particle.contrainToBounds(WIDTH, HEIGHT, PARTICLE_RADIUS);
		}

		for (size_t ii = 0; ii < 5; ii++)
		{
			for (auto& constraint : constraints)
			{
				constraint.satisfy();
			}
		}

		window.clear(sf::Color::Black);

		// Draw particles
		for (const auto& particle : particles)
		{
			sf::CircleShape circle(PARTICLE_RADIUS);
			circle.setFillColor(sf::Color::White);
			circle.setPosition(particle.pos.x - PARTICLE_RADIUS,
								particle.pos.y - PARTICLE_RADIUS);
			
			window.draw(circle);
		}

		// Draw constraints as lines
		for (const auto& constraint : constraints)
		{
			sf::Vertex line[] = {
				sf::Vertex(constraint.p1->pos,sf::Color::White),
				sf::Vertex(constraint.p2->pos, sf::Color::White)
			};

			window.draw(line, 2, sf::Lines);
		}

		window.display();
	}
}