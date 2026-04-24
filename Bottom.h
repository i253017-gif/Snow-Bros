#pragma once
#include "Enemy.h"
class Botom :public Enemy {
	public:
	Botom(float x, float y,float speed_mult, int extra_hits);
	
	
	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float time) override;
	~Botom();
};