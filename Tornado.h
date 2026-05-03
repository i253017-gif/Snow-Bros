#pragma once
#include "FlyingFooga.h"
#include"knife.h"

class Tornado :public FlyingFooga {
protected:
	float knife_timer;  //counts down to next knife throw
	float teleportTime;
	float currentTime;
	knife* knives[200]; 
	int knifeNum;
	float playerX, playerY;

public:
	Tornado(float x, float y, float speed_mult, int extra_hits);

	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float time) override;
	sf::FloatRect getBounds() override;
	std::string get_type() const override;

	void set_player_position(float x, float y);  

	float get_knife_timer();
	void set_knife_timer(float time);

	void Teleport();
	~Tornado();
};