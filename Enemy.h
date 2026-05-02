#pragma once
#include <SFML/Graphics.hpp>
#include <string> // ADDED

enum EnemyType { BOTOM, TORNADO, FLYING_FOOGA, MOGERA, GAMAKICHI, MOGERA_CHILD };

class Enemy {
protected:
	EnemyType type;
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

	// ADDED: so derived classes can override properly (Botom already does)
	virtual std::string get_type() const = 0;
	EnemyType getEnemyType() const { return type; }

	//enemyneeds to be daMAGED MORE if its hp isnt 0 and if its 0 it dies
	void take_damage(int amount);

	// ADDED: snow-only hit control for Snowball Power (encase in 1 hit)
	int get_snow_hits_needed() const;
	void set_snow_hits_needed(int hits);
	void apply_snow_hit(int amount);

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
