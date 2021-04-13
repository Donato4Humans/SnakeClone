#include <time.h>
#include "Snake.h"


Snake::Snake(sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed, unsigned direction) 
	: animation(texture, imageCount, switchTime)
	, speed(speed)
	, direction(direction)
	, row(0)
	, turn(false)
	, left(false)
	, right(false)
	, movement(0.0f, 0.0f)
	, animationDirection(6)
{
	body.setSize(sf::Vector2f(16.0f, 16.0f));
	body.setPosition(240.0f, 240.0f);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(&texture);
}

Snake::~Snake()
{
}

//void Snake::Debug(sf::Vector2f move, bool left, bool right)
//{
//  //std::cout << left << " = LEFT\n" << right << " = RIGHT\n";
//	std::cout << move.x << " - X\n" << move.y << " - Y\n";
//}

void Snake::setStartDirection(std::vector<Snake>& snakeBody)
{
	srand(time(0));

	int startDirection = 1 + rand() % 4;

	switch (startDirection)
	{
	case 1:
		animationDirection = 1;
		movement.x = speed;
		movement.y = 0.0f;
		break;

	case 2:
		animationDirection = 2;
		movement.y = speed;
		movement.x = 0.0f;
		break;

	case 3:
		animationDirection = 3;
		movement.x = -speed;
		movement.y = 0.0f;
		break;

	case 4:
		animationDirection = 4;
		movement.y = -speed;
		movement.x = 0.0f;
		break;
	}
	for (int i = 0; i < snakeBody.size(); i++)
	{
		snakeBody[i].direction = animationDirection;
	}
}

void Snake::Turning(std::vector<Snake>& snakeBody)
{
	while (movement.x != 0.0f || movement.y != 0)
	{
		if (movement.y == 0.0f)
		{
			if (right && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				right = false;

				//previousDirections.push_back(animationDirection);
				animationDirection++;

				//previousMovements.push_back(movement);
				movement.y = movement.x;
				movement.x = 0.0f;

				break;
			}
			else if (left && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				left = false;

				//previousDirections.push_back(animationDirection);
				animationDirection--;

				//previousMovements.push_back(movement);
				movement.y = -movement.x;
				movement.x = 0.0f;

				break;
			}
		}
		if (movement.x == 0.0f)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && right)
			{
				right = false;

				//previousDirections.push_back(animationDirection);
				animationDirection++;

				//previousMovements.push_back(movement);
				movement.x = -movement.y;
				movement.y = 0.0f;

				break;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && left)
			{
				left = false;

				//previousDirections.push_back(animationDirection);
				animationDirection--;

				//previousMovements.push_back(movement);
				movement.x = movement.y;
				movement.y = 0.0f;

				break;
			}
		}
		if (animationDirection == 5)
			animationDirection = 1;
		else if (animationDirection < 1)
			animationDirection = 4;

		snakeBody.front().direction = animationDirection;

		break;
	}
}

//void Snake::addBodySegment(std::vector<Snake>& snakeBody, sf::Texture& texture)
//{
//	//add copying of direction from previous object in array
//	Snake segment(texture, sf::Vector2u(4, 4), 0.3f, 2.0f, 0);
//	snakeBody.push_back(segment);
//}

void Snake::setFollowingNextToTurnObjectPosition(std::vector<Snake>& snakeBody, int& i)
{
	switch (snakeBody[i].direction)
	{
		case 1:
			snakeBody[i].body.setPosition(snakeBody[i - 1].body.getPosition().x - 16.0f,
										  snakeBody[i - 1].body.getPosition().y);
			break;
		case 2:
			snakeBody[i].body.setPosition(snakeBody[i - 1].body.getPosition().x,
										  snakeBody[i - 1].body.getPosition().y - 16.0f);
			break;
		case 3:
			snakeBody[i].body.setPosition(snakeBody[i - 1].body.getPosition().x + 16.0f,
										  snakeBody[i - 1].body.getPosition().y);
			break;
		case 4:
			snakeBody[i].body.setPosition(snakeBody[i - 1].body.getPosition().x,
										  snakeBody[i - 1].body.getPosition().y + 16.0f);
			break;
	}
}

void Snake::setObjectPosition(std::vector<Snake>& snakeBody, int& i)
{
	if (snakeBody[i - 1].turn == true)
	{
		setFollowingNextToTurnObjectPosition(snakeBody, i);
		return;
	}
	switch (snakeBody[i - 1].direction)
	{
		case 1:
			snakeBody[i].body.setPosition(snakeBody[i - 1].body.getPosition().x - 16.0f,
										  snakeBody[i - 1].body.getPosition().y);

			if (snakeBody[i].turn == true)
			{
				snakeBody[i].direction = snakeBody[i - 1].direction;
			}
			break;
		case 2:
			snakeBody[i].body.setPosition(snakeBody[i - 1].body.getPosition().x,
										  snakeBody[i - 1].body.getPosition().y - 16.0f);

			if (snakeBody[i].turn == true)
			{
				snakeBody[i].direction = snakeBody[i - 1].direction;
			}
			break;
		case 3:
			snakeBody[i].body.setPosition(snakeBody[i - 1].body.getPosition().x + 16.0f,
										  snakeBody[i - 1].body.getPosition().y);

			if (snakeBody[i].turn == true)
			{
				snakeBody[i].direction = snakeBody[i - 1].direction;
			}
			break;
		case 4:
			snakeBody[i].body.setPosition(snakeBody[i - 1].body.getPosition().x,
										  snakeBody[i - 1].body.getPosition().y + 16.0f);

			if (snakeBody[i].turn == true)
			{
				snakeBody[i].direction = snakeBody[i - 1].direction;
			}
			break;
	}
	snakeBody[snakeBody.size() - 1].direction = snakeBody[snakeBody.size() - 2].direction;// change it later
}

void Snake::updatePosition(std::vector<Snake>& snakeBody)
{
	for (int i = 1; i < snakeBody.size(); i++)
	{
		/*if (snakeBody[1].direction != snakeBody[0].direction)
		{
			snakeBody[1].turn = true;
		}*/

		if (snakeBody[i].turn == true)
		{
			turnIndexes.push_back(i);
		}

		setObjectPosition(snakeBody, i);
		/*switch (snakeBody[i].direction)
		{
		case 1:
			setObjectPosition(snakeBody, i);
			break;
		case 2:
			setObjectPosition(snakeBody, i);
			break;
		case 3:
			setObjectPosition(snakeBody, i);
			break;
		case 4:
			setObjectPosition(snakeBody, i);
			break;
		}*/
	}
}

void Snake::Update(float deltaTime, std::vector<Snake>& snakeBody, sf::Texture& texture)
{
	if (movement.x == 0.0f && movement.y == 0.0f)
	{
		setStartDirection(snakeBody);
	}

	Turning(snakeBody);

	snakeBody.front().body.move(movement);
	
	updatePosition(snakeBody);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//{
	//	addBodySegment(snakeBody, texture);
	//}

	for (int i = 0; i < snakeBody.size(); i++)
	{
		if (snakeBody[i].turn == true && i < snakeBody.size() - 1)
		{
			row = 2;
			animation.Update(row, deltaTime, animationDirection, snakeBody[i + 1].direction, snakeBody[i].direction);// 1 in last [] 
			snakeBody[i].body.setTextureRect(animation.uvRect);
			continue;
		}

		if (i > 0 && i < snakeBody.size() - 1)
		{
			row = 3;
			animation.Update(row, deltaTime, snakeBody[i].direction, 1, 1);
		}
		else if (i == snakeBody.size() - 1)
		{
			row = 1;
			animation.Update(row, deltaTime, snakeBody[i].direction, 1, 1);
		}
		else
		{
			row = 0;
			animation.Update(row, deltaTime, animationDirection, 1, 1);
		}
		snakeBody[i].body.setTextureRect(animation.uvRect);
	}

	if (turnIndexes.size() > 0)
	{
		for (int i = 0; i < turnIndexes.size(); i++)
		{
			snakeBody[turnIndexes[i]].turn = false;
		}
		for (int i = 0; i < turnIndexes.size(); i++)
		{
			snakeBody[turnIndexes[i] + 1].turn = true;
		}
		turnIndexes.clear();
	}

	if (snakeBody[snakeBody.size() - 1].turn == true)
	{
		snakeBody[snakeBody.size() - 1].turn = false;
	}
	/*for (int i = 1; i < snakeBody.size() - 1; i++)
	{
		if (snakeBody[i].turn == true)
		{
			snakeBody[i].turn = false;
			break;
		}
	}*/

}

void Snake::Draw(sf::RenderWindow & window, std::vector <Snake>& snakeBody)
{
	for (int i = 0; i < snakeBody.size(); i++)
	{
		window.draw(snakeBody[i].body);
	}
}
