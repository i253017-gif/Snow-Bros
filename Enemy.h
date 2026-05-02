#pragma once

#include <SFML/Graphics.hpp>
  


class Enemy {
protected:
	sf::RectangleShape shape;
	sf::Sprite visual;
	sf::Texture text;
	//enemy positions
	float pos_x;
	float pos_y;
	//enemy speed
	float speed;
	int hp; //remaining health
	int snow_hits_needed;//hits needed for the enemy to get encased in snow
	bool encased; //whether the enemy if cpvered with snow yet or not
	bool isOnGround;
	float velocityY;
	
public:
	Enemy(float hor, float vert, float s, int health, int hit);
	virtual ~Enemy();

	//pure virtual funcs which make the class abstract

	virtual void update(float delta_time) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void move(float delta_time) = 0;
	virtual sf::FloatRect getBounds() = 0; //hitbox
	//enemyneeds to be daMAGED MORE if its hp isnt 0 and if its 0 it dies
	void take_damage(int amount);

	//GETTERS AND SETTERS 
	float get_pos_x();
	float  get_pos_y();
	int   get_hp();
	float get_speed();
	bool  get_encased();

	void set_pos_x(float x);
	void set_pos_y(float y);
	void set_speed(float spd);
	void set_encased(bool state);


	void setOnGround(bool onGround);
	float getVelocity();
	void setVelocity(float v);
	void newPosition(float x, float y);
};
