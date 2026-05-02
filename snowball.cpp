#include<SFML/Graphics.hpp>
#include"snowball.h"
#include<cmath>

Snowball::Snowball(float startX, float startY, float direction, float speed, float range)
{
	shape.setRadius(5);
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(startX, startY);

	texture.loadFromFile("Nick.png");
	sprite.setTexture(texture);

	sprite.setTextureRect(sf::IntRect(81, 3564, 172, 12));
	sprite.setPosition(startX, startY);
	sprite.setScale(0.5f, 0.5f);

	velocityY = 0.0f;
	velocityX = direction * 2.0f;
	gravity = 0.05f;
	isActive = true;
	distanceTraveled = 0.0f;
	maxDistance = range;
}

void Snowball::update()
{
	velocityY += gravity;

	shape.move(velocityX, velocityY);
	sprite.move(velocityX, velocityY);


	//wrapping
	if (shape.getPosition().x > 600)
	{
		shape.setPosition(-10, shape.getPosition().y);
		sprite.setPosition(-10, shape.getPosition().y);

	}
	else if (shape.getPosition().x < -10)
	{
		shape.setPosition(610, shape.getPosition().y);
		sprite.setPosition(610, shape.getPosition().y);
	}

	//snowball end
	distanceTraveled += std::abs(velocityX);
	if (distanceTraveled > maxDistance)
		isActive = false;
}

void Snowball::render(sf::RenderWindow& window)
{
	if (isActive)
	{
		window.draw(sprite);
	}
}

void Snowball::setInactive()
{
	isActive = false;
}
bool Snowball::getActivity()
{
	return isActive;
}

sf::FloatRect Snowball::getBounds()
{
	return shape.getGlobalBounds();
}



// Default constructor bcs we need to make array of snowballs and it needs default
Snowball::Snowball()
{
	shape.setRadius(8);
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(0, 0);

	texture.loadFromFile("Nick.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(40, 490, 32, 32));
	sprite.setPosition(0, 0);

	velocityX = 0.0f;
	velocityY = 0.0f;
	gravity = 0.15f;
	isActive = false;  // Start inactive
	maxRange = 0.0f;
	distanceTraveled = 0.0f;
}
