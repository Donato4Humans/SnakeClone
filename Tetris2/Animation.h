#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture& texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void Update(int row, float deltaTime, size_t animationDirection, size_t previousDirection, size_t currentDirection);

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

