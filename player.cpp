#include<SFML/Graphics.hpp>
#include"player.h"
#include"inputmanager.h"


Player::Player()
{
	shape.setSize(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(300, 600); //hard coding ts for now
	//texture.loadFromFile()
	//spriet.setTexture(texture);
	//sprite.setPosition(shape.getPosition())   superimposes on top of hitbox
	velocityX = 0.5f;  //5 frames per sec when key is pressed
	velocityY = 0.0f;
	gravity = 0.05f;
	Jumpstrength = -5.0f; //negative to go up????
	isOnGround = false;
	facingDirection = 1;     //start game by facing right
	wasSpacePressed = false;

	///////============ADDED BY ISHMALLLLL============////

	snowball_power = false;
	snowball_distance = 500.0f;
	org_distance = 500.0f;
	balloon_mode = false;



}
void Player::handleInput(inputManager& input)
{
	if (input.isLeftPressed())
	{
		shape.move(-velocityX, 0); //move left
		facingDirection = -1;
	}
	if (input.isRightPressed())
	{
		shape.move(velocityX, 0); //move right
		facingDirection = 1;
	}

	if (input.isUpPressed() && !wasSpacePressed)
	{
		velocityY = Jumpstrength;
		isOnGround = false;
		wasSpacePressed = true;
	}
	else if (!input.isUpPressed())
		wasSpacePressed = false;

}

sf::FloatRect Player::getBounds()
{
	return shape.getGlobalBounds();
}

void Player::applyGravity() {
	velocityY += gravity;
}

int Player::getFacingDirection()		//for snowball
{
	return facingDirection;
}

float Player::getVelocity()
{
	return velocityY;  // Returns current falling speed
}

void Player::setVelocity(float v)
{
	velocityY = v;   // Set falling speed (0 = stop falling)
}

void Player::newPosition(float x, float y)
{
	shape.setPosition(x, y);    // Move the circle hitbox
	//sprite.setPosition(x, y);   // Move the visual sprite too
}

void Player::setOnGround(bool onGround)
{
	isOnGround = onGround;
}
void Player::update()
{
	applyGravity();   //apply gravity every frame
	shape.move(0, velocityY); //move vertically

	// =========================
  // GROUND
  // =========================
	if (shape.getPosition().y >= 550) {
		shape.setPosition(shape.getPosition().x, 550);
		velocityY = 0;
		isOnGround = true;
	}

	/////////======ADDED BY ISHMALLLLLLLLLLLLL TO UPDATE POWER UP EFFECTS========///////

	// balloon mode - float upward
	if (balloon_mode) {
		velocityY = -1.0f;
	}
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(shape);
}

////////==========ADDED BY ISHMALLLLLLLLLLLLL TO USE IN POWER UP CLASSES=============//////

bool  Player::get_snowball_power() { 
	return snowball_power;
}
void  Player::set_snowball_power(bool state) {
	snowball_power = state; 
}
float Player::get_snowball_distance() {
	return snowball_distance;
}
void  Player::set_snowball_distance(float d) { 
	snowball_distance = d; 
}
bool  Player::get_balloon_mode() { 
	return balloon_mode; 
}
void  Player::set_balloon_mode(bool state) { 
	balloon_mode = state; 
}
float Player::get_speed() {
	return velocityX; 
}
void  Player::set_speed(float v) { 
	velocityX = v; 
}
