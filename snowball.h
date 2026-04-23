#pragma once
#include<SFML/Graphics.hpp>

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

public:
	Snowball();
	Snowball(float startX, float startY, float direction, float speed=5.0f, float range=500.0f);


	void update();
	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds();
	void setInactive();
	bool getActivity();
};
