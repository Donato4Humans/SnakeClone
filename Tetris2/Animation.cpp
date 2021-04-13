#include "Animation.h"


Animation::Animation(sf::Texture& texture, sf::Vector2u imageCount, float switchTime) 
	: imageCount(imageCount)
	, switchTime(switchTime)
	, totalTime(0.0f)
{
	currentImage.x = 0;

	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime, size_t animationDirection, size_t previousDirection, size_t currentDirection)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (row == 2)
	{
		switch (previousDirection)
		{
		case 1:
			if (currentDirection == 2)
			{
				currentImage.x = 2;
				uvRect.left = currentImage.x * uvRect.width;
			}
			else if (currentDirection == 4)
			{
				currentImage.x = 3;
				uvRect.left = currentImage.x * uvRect.width;
			}
			break;
		case 2:
			if (currentDirection == 1)
			{
				currentImage.x = 0;
				uvRect.left = currentImage.x * uvRect.width;
			}
			else if (currentDirection == 3)
			{
				currentImage.x = 3;
				uvRect.left = currentImage.x * uvRect.width;
			}
			break;
		case 3:
			if (currentDirection == 2)
			{
				currentImage.x = 1;
				uvRect.left = currentImage.x * uvRect.width;
			}
			else if (currentDirection == 4)
			{
				currentImage.x = 0;
				uvRect.left = currentImage.x * uvRect.width;
			}
			break;
		case 4:
			if (currentDirection == 1)
			{
				currentImage.x = 1;
				uvRect.left = currentImage.x * uvRect.width;
			}
			else if (currentDirection == 3)
			{
				currentImage.x = 2;
				uvRect.left = currentImage.x * uvRect.width;
			}
			break;
		}
	}
	else if (row == 3)
	{
		switch (animationDirection)
		{
		case 1 : case 3:
			currentImage.x = 1;
			uvRect.left = currentImage.x * uvRect.width;
			break;
		case 2: case 4:
			currentImage.x = 0;
			uvRect.left = currentImage.x * uvRect.width;
			break;
		}
	}
	else
	{
		switch (animationDirection)
		{
		case 1:
			currentImage.x = animationDirection;
			uvRect.left = currentImage.x * uvRect.width;
			break;
		case 2:
			currentImage.x = animationDirection;
			uvRect.left = currentImage.x * uvRect.width;
			break;
		case 3:
			currentImage.x = animationDirection;
			uvRect.left = currentImage.x * uvRect.width;
			break;
		case 4:
			currentImage.x = 0;
			uvRect.left = currentImage.x * uvRect.width;
			break;
		}
	}
}
