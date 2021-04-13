#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

#include <iostream>
#include <vector>

enum class Position
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3
};

class Snake
{
public:
	Snake(sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed, unsigned direction);
	~Snake();

	void Update(float deltaTime, std::vector<Snake>& snakeBody, sf::Texture& texture);
	void Draw(sf::RenderWindow& window, std::vector<Snake>& snakeBody);

	//void Debug(sf::Vector2f move, bool left, bool right);
	//void addBodySegment(std::vector<Snake>& snakeBody, sf::Texture& texture);

public:
	bool left;
	bool right;

private:
	void setStartDirection(std::vector<Snake>& snakeBody);
	void Turning(std::vector<Snake>& snakeBody);

	void setObjectPosition(std::vector<Snake>& snakeBody, int& i);
	void setFollowingNextToTurnObjectPosition(std::vector<Snake>& snakeBody, int& i);
	//void setPreviousPosition(std::vector<Snake>& snakeBody, int& i, size_t& turnedObj, Position position);
	//void setCurrentPosition(std::vector<Snake>& snakeBody, int& i, Position position);

	void updatePosition(std::vector<Snake>& snakeBody);
	//void addBodySegment(std::vector<Snake>& snakeBody, sf::Texture& texture);

private: 
	sf::RectangleShape body;
	sf::Vector2f movement;

	std::vector<size_t> turnIndexes;
	//std::vector<size_t> previousDirections;
	//std::vector<sf::Vector2f> previousMovements;

	Animation animation;

	bool turn;
	float speed;
	size_t row;
	size_t direction;
	size_t animationDirection;
};


