#include <SFML/Graphics.hpp>
#include <vector>

#include "Particle.h"
#include "Constraint.h"

const int WIDTH = 1080;
const int HEIGHT = 720;
const float PARTICLE_RADIUS = 30.0f;
const float GRAVITY = 9.8f;
const float TIME_STEP = 0.1f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");
	window.setFramerateLimit(60);

	std::vector<Particle> particles;
	particles.emplace_back(WIDTH / 2 - 50, HEIGHT / 2 - 50);
	particles.emplace_back(WIDTH / 2 - 50, HEIGHT / 2 + 50);
	particles.emplace_back(WIDTH / 2 + 50, HEIGHT / 2 - 50);
	particles.emplace_back(WIDTH / 2 + 50, HEIGHT / 2 + 50);

	std::vector<Constraint> constraints;
	constraints.emplace_back(&particles[0], &particles[1]);
	constraints.emplace_back(&particles[0], &particles[2]);
	constraints.emplace_back(&particles[0], &particles[3]);
	constraints.emplace_back(&particles[1], &particles[2]);
	constraints.emplace_back(&particles[1], &particles[3]);
	constraints.emplace_back(&particles[2], &particles[3]);
	

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