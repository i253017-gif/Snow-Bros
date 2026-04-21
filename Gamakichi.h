#pragma once
#include"Boss.h"
class Gamakichi :public Boss {
	float rocket_timer;
	int   gem_reward;

public:
	Gamakichi(float x, float y, int hp);
	~Gamakichi();

	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float delta_time) override;

	//setters and gettersg
	float get_rocket_timer();
	int get_gem_reward();
	void set_rocket_timer(float time);
	void set_gem_reward(int reward);

};