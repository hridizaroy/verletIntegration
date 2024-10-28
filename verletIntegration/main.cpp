#include <SFML/Graphics.hpp>
#include <vector>

#include "particle.h"

const int WIDTH = 1080;
const int HEIGHT = 720;
const float PARTICLE_RADIUS = 30.0f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");

	std::vector<Particle> particles;
	particles.emplace_back(WIDTH / 2, HEIGHT / 2);

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

		window.clear(sf::Color::Black);

		// Draw particles
		for (const auto& particle : particles)
		{
			sf::CircleShape circle(PARTICLE_RADIUS);
			circle.setFillColor(sf::Color::White);
			circle.setPosition(particle.pos);
			
			window.draw(circle);
		}

		window.display();
	}
}