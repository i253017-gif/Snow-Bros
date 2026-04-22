#pragma once
#include"Projectile.h"
class knife : public Projectile {
public:
	knife(float x, float y, float vx, float vy);


	//overriden funcs
	void draw(sf::RenderWindow& window) override;
	void update(float time) override;
	void on_hit() override;

	~knife() {}






};