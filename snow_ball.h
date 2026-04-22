#pragma once
#include"Projectile.h"
class snow_ball : public Projectile {
public:
	snow_ball(float x, float y, float vx, float vy);


	//overriden funcs
	void draw(sf::RenderWindow& window) override;
	void update(float time) override;
	void on_hit() override;

	~snow_ball(){}






};