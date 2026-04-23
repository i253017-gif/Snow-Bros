#include<SFML/Graphics.hpp>
#include"player.h"
#include"inputmanager.h"

Player::Player()
{
	shape.setSize(sf::Vector2f(50,50));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(300, 300); //hard coding ts for now
	//texture.loadFromFile()
	//spriet.setTexture(texture);
	//sprite.setPosition(shape.getPosition())   superimposes on top of hitbox
	velocityX = 5.0f;  //5 frames per sec when key is pressed
	velocityY = 0.0f;
	gravity = 0.5f;
	Jumpstrength = -10.0f; //negative to go up????
	isOnGround = false;

}
void Player::handleInput(inputManager& input)
{
	if(input.isLeftPressed())
		shape.move(-velocityX, 0); //move left
	if(input.isRightPressed())
		shape.move(velocityX, 0); //move right
	if (input.isUpPressed())
	{
		velocityY = Jumpstrength;
		isOnGround = false;  
	}

}
void Player::update()
{
	applyGravity();   //apply gravity every frame
	shape.move(0, velocityY); //move vertically

	// =========================
  // TEMPORARY GROUND (REMOVE LATER)
  // =========================
	if (shape.getPosition().y >= 500) {
		shape.setPosition(shape.getPosition().x, 500);
		velocityY = 0;
		isOnGround = true;
	}
}
sf::FloatRect Player::getBounds()
{
	return shape.getGlobalBounds();
}
void Player::render(sf::RenderWindow& window)
{
	window.draw(shape);
}
void Player::applyGravity() {
	velocityY += gravity;
}
