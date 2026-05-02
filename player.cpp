#include<SFML/Graphics.hpp>
#include"player.h"
#include"inputmanager.h"
#include<cmath>

Player::Player()
{
	shape.setSize(sf::Vector2f(50,50));
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

	lives = 2;
	score = 0;
	invincibilityTime = 0.0f;
	

}
void Player::handleInput(inputManager& input)
{
	if(input.isLeftPressed())
	{ 
		shape.move(-velocityX, 0); //move left
		facingDirection = -1;
	}
	if(input.isRightPressed())
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

int Player:: getFacingDirection()		//for snowball
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


	if (invincibilityTime > 0.0f)
		invincibilityTime -= 0.016f;
	// =========================
  // GROUND
  // =========================
	if (shape.getPosition().y >= 550) {
		shape.setPosition(shape.getPosition().x, 550);
		velocityY = 0;
		isOnGround = true;
	}
}

void Player::render(sf::RenderWindow& window)
{

	if (isInvincible())
	{
		if (fmod(invincibilityTime, 0.2f)<0.1f)
		{
			window.draw(shape);
		}
	}
	else
	{
		window.draw(shape);
	}
}

int Player::getLives()
{
	return lives;
}

void Player::loseLive()
{
	lives--;
	resetToStart();
	invincibilityTime = 20.0f;
}

void Player::resetToStart()
{
	shape.setPosition(300, 600);
	//sprite.setPosition(shape.getPosition());
	isOnGround = false;
}

bool Player::isInvincible()
{
	return (invincibilityTime > 0.0f);
}

void Player::addScore(int points)
{
	score += points;
}

int Player::getScore() 
{
	return score;
}

void Player::set_speed(float speed) {
	velocityX = speed;
}

float Player::get_speed() {
	return velocityX;
}

void Player::set_snowball_power(bool active) {
	// You need a member variable: bool snowball_power_active;
	snowball_power_active = active;
}

void Player::set_snowball_distance(float distance) {
	// You need a member variable: float snowball_distance;
	snowball_distance = distance;
}

float Player::get_snowball_distance() {
	return snowball_distance;
}

void Player::set_balloon_mode(bool active) {
	// You need a member variable: bool balloon_mode_active;
	balloon_mode_active = active;
}

void Player::addGems(int amount)
{
	gem += amount;
}

int Player::getGems() 
{
	return gem;
}
