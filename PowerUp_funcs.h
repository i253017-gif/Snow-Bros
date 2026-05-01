#pragma once
#include<string>
#include "PowerUp.h"
#include"player.h"
class Player;
class PowerUp_funcs : public PowerUp {
	std::string powerup_type;   // the type of powerup
	float       timer;//the duration of power up effect
	float original_distance;
public:
	PowerUp_funcs(std::string type, float x, float y);//pass the power up type and position where enemy dies cz 
	//the power up will spawn at the position of enemy death
	void apply_speed(Player& p);
	void apply_snowball(Player& p);
	void apply_distance(Player& p);
	void apply_balloon(Player& p);
	void update(float delta_time);
	//pverriding the pure virtual functions
	void apply(Player& p) override;
	void draw(sf::RenderWindow& window) override;
	void expire(Player& p) override;

	std::string get_powerup_type();
	float  get_timer();

	//there is no need for setters as the power up type and position will be set in the constructor and they wont change during the game

	~PowerUp_funcs();
};
