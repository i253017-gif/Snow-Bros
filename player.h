#pragma once
#include<SFML/Graphics.hpp>
#include"inputmanager.h"
#include"player.h"
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
	bool wasSpacePressed;

	///=========ADDED BYYYYY ISHMALLLLLLLLLLLL//
	//============POWER UP RELATED VARISBLES=========///

	bool  snowball_power;      //snow ball power(power ups)
	float snowball_distance;   //updated distance due to powe up
	float org_distance;       //snowballs org distance to reset after power up expires
	bool  balloon_mode;
public:
	Player();

	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
	void applyGravity();
	int getFacingDirection();

	float getVelocity();
	void setVelocity(float v);
	void newPosition(float x, float y);

	void setOnGround(bool onGround);

	//=======ADDED BY ISHMALLLLLLLLLLLLL TO USE IN POWER UP CLASSES=============//////
	bool  get_snowball_power();
	void  set_snowball_power(bool state);
	float get_snowball_distance();
	void  set_snowball_distance(float d);
	bool  get_balloon_mode();
	void  set_balloon_mode(bool state);

	float get_speed();
	void  set_speed(float v);

	sf::FloatRect getBounds(); //hitbox
};