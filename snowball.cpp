// snowball.cpp
#include<SFML/Graphics.hpp>
#include"snowball.h"
#include<cmath>

Snowball::Snowball(float startX, float startY, float direction, float speed, float range)
{
	shape.setRadius(15);
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(startX, startY);

	//texture.loadFromFile("Nick.png");
	//sprite.setTexture(texture);

	//sprite.setTextureRect(sf::IntRect(81, 3564, 172, 12));
	//sprite.setPosition(startX, startY);
	//sprite.setScale(0.5f, 0.5f);

	velocityY = -3.0f;
	velocityX = direction * 5.0f;
	gravity = 0.25f;
	isActive = true;
	distanceTraveled = 0.0f;
	maxDistance = range;

	// ADDED: frozen enemy properties
	isFrozenEnemy = false;
	frozenTimer = 0.0f;
	frozenMaxTimer = 10.0f;
	frozenEnemyType = -1;
	isOnGround = false;
}

void Snowball::update()
{
	// ADDED: frozen enemy snowball behavior
	if (isFrozenEnemy)
	{
		frozenTimer += 0.016f;
		if (frozenTimer >= frozenMaxTimer)
		{
			isActive = false;
			return;
		}

		velocityY += gravity;
		shape.move(velocityX, velocityY);

		// ADDED: ground boundary for frozen snowball
		if (shape.getPosition().y >= 550)
		{
			shape.setPosition(shape.getPosition().x, 550);
			velocityY = 0.0f;
			isOnGround = true;
		}

		return;
	}

	velocityY += gravity;

	shape.move(velocityX, velocityY);
	sprite.move(velocityX, velocityY);

	// ADDED: ground boundary for regular snowballs
	if (shape.getPosition().y >= 550)
	{
		shape.setPosition(shape.getPosition().x, 550);
		velocityY = 0.0f;
		isOnGround = true;
	}

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
		// ADDED: render frozen enemy as larger cyan snowball
		if (isFrozenEnemy)
		{
			sf::CircleShape frozenShape(25);
			frozenShape.setFillColor(sf::Color::Yellow);
			frozenShape.setPosition(shape.getPosition());
			window.draw(frozenShape);
		}
		else
		{
			//window.draw(sprite);
			window.draw(shape);
		}
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
	// ADDED: larger hitbox for frozen enemy
	if (isFrozenEnemy)
	{
		return sf::FloatRect(shape.getPosition().x - 10, shape.getPosition().y - 10, 80, 80);
	}
	return shape.getGlobalBounds();
}

// ADDED: freeze enemy into snowball
void Snowball::freezeEnemy(int enemyType, float x, float y)
{
	isFrozenEnemy = true;
	frozenEnemyType = enemyType;
	frozenTimer = 0.0f;
	shape.setPosition(x, y);
	velocityX = (rand() % 2 == 0) ? -1.2f : 1.2f; // Random horizontal movement
	velocityY = 0.0f;
	isActive = true;
	distanceTraveled = 0.0f;
}

// ADDED: check if this is a frozen enemy snowball
bool Snowball::isFrozen() const
{
	return isFrozenEnemy;
}

// ADDED: get frozen enemy type
int Snowball::getFrozenEnemyType() const
{
	return frozenEnemyType;
}

// Default constructor bcs we need to make array of snowballs and it needs default
Snowball::Snowball()
{
	shape.setRadius(15);
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

	// ADDED: prevent uninitialized use
	maxDistance = 0.0f;

	// ADDED: frozen enemy defaults
	isFrozenEnemy = false;
	frozenTimer = 0.0f;
	frozenMaxTimer = 10.0f;
	frozenEnemyType = -1;
	isOnGround = false;
}