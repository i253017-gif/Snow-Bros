#pragma once
#include "FlyingFooga.h"
class Tornado :public FlyingFooga{
protected:
	float knife_timer; //it keeps throwing knives so its a timer for hoq long one knife is there before the other one is thrown
public:
	Tornado(float x, float y, float speed_mult, int extra_hits);


	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float time) override;
	

	//getter ND setters
	float get_knife_timer();
	void set_knife_timer(float time);

	~Tornado();
};