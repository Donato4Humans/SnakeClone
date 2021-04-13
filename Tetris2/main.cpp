#include <SFML/Graphics.hpp>
#include "Snake.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(480, 480), "SNAKE!");
	window.setFramerateLimit(1);
	
	sf::Texture t;
	t.loadFromFile("textures/Snake.png");

	sf::Sprite background;
	background.setTexture(t);

	std::vector<Snake> snakeBody( { Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0),
									Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0) } );

	//snakeBody.front().addBodySegment(snakeBody, t);
	snakeBody.push_back(Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0));//3
	snakeBody.push_back(Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0));//4
	snakeBody.push_back(Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0));//5
	snakeBody.push_back(Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0));//6
	snakeBody.push_back(Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0));//7
	snakeBody.push_back(Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0));//8
	snakeBody.push_back(Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0));//9
	snakeBody.push_back(Snake(t, sf::Vector2u(4, 4), 0.3f, 16.0f, 0));//10

	sf::Vector2u textureSize = t.getSize();
	sf::Vector2u windowSize = window.getSize();
	textureSize.x /= 4;
	textureSize.y /= 4;
	float scaleX = windowSize.x / textureSize.x;
	float scaleY = windowSize.y / textureSize.y;

	background.setTextureRect(sf::IntRect(textureSize.x * 3, textureSize.y * 3, textureSize.x, textureSize.y));
	background.setScale(scaleX, scaleY);

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
			}
			if (sf::Event::KeyPressed)
				if (evnt.key.code == sf::Keyboard::A)
				{
					//snakeBody.front().addBodySegment(snakeBody, t);
					snakeBody.front().right = false;
					snakeBody.front().left = true;
				}
				else if (evnt.key.code == sf::Keyboard::D)
				{
					snakeBody.front().left = false;
					snakeBody.front().right = true;
				}
		}

		snakeBody[0].Update(deltaTime, snakeBody, t);

		window.clear(sf::Color::Black);
		window.draw(background);
		snakeBody[0].Draw(window, snakeBody);
		window.display();
	}

	return 0;
}