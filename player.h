#pragma once
#include<SFML/Graphics.hpp>
#include"inputmanager.h"

class Player
{
private:
	sf::RectangleShape shape;      //player shape and like the hitbox shape as well
	float velocityX;			   //per frame movement rate
	float velocityY;
	float gravity;
	float Jumpstrength;
	bool isOnGround; 	           //no double jump
	int facingDirection;
	bool wasSpacePressed;

	int lives;
	int score;
	int gem;
	float invincibilityTime;

	bool snowball_power_active;
	float snowball_distance;
	float original_snowball_distance;
	bool balloon_mode_active;

public:
	Player();

	void handleInput(inputManager& input, int p);
	void update();
	void render(sf::RenderWindow& window);
	void applyGravity();
	int getFacingDirection();

	float getVelocity();
	void setVelocity(float v);
	void newPosition(float x, float y);

	void setOnGround(bool onGround);

	sf::FloatRect getBounds(); //hitbox

	int getLives();
	void loseLive();
	void resetToStart();    //after death
	bool isInvincible();
	int getScore();
	void addScore(int points);
	void addGems(int amount);
	int getGems();

	void set_speed(float speed);
	float get_speed();
	void set_snowball_power(bool active);
	void set_snowball_distance(float distance);
	float get_snowball_distance();
	void set_balloon_mode(bool active);

	// ADDED: getters needed by playState
	bool isSnowballPowerActive() const;
	bool isBalloonModeActive() const;
};