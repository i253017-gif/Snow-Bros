// snowball.h
#pragma once
#include <SFML/Graphics.hpp> 
#include "player.h"
class Player;

class Snowball
{
private:
	sf::CircleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;

	float velocityX;
	float velocityY;
	float gravity;

	bool isActive;
	float maxRange;
	float distanceTraveled;
	float maxDistance; //for range limit

	// ADDED: frozen enemy snowball properties
	bool isFrozenEnemy;
	float frozenTimer;
	float frozenMaxTimer;
	int frozenEnemyType; // Store enemy type to check if boss
	bool isOnGround;

public:
	Snowball();
	Snowball(float startX, float startY, float direction, float speed = 5.0f, float range = 500.0f);

	void update();
	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds();
	void setInactive();
	bool getActivity();

	// ADDED: frozen enemy snowball methods
	void freezeEnemy(int enemyType, float x, float y);
	bool isFrozen() const;
	int getFrozenEnemyType() const;
};