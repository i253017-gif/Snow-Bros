#pragma once
#include<SFML/Graphics.hpp>
#include"inputmanager.h"

class Player
{
private:
	sf::RectangleShape shape;      //player shape and like the hitbox shape as well
	//sf::Sprite sprite;             
	//sf::Texture texture;
	float velocityX;			   //per frame movement rate
	float velocityY;
	float gravity;
	float Jumpstrength;
	bool isOnGround; 	           //no double jump
	int facingDirection; 
public:
	Player();

	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
	void applyGravity();
	int getFacingDirection();

	sf::FloatRect getBounds(); //hitbox
};
