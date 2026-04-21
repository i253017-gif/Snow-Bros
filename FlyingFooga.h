#pragma once
#include "Bottom.h"
class FlyingFooga :public Botom {
protected:
	bool  flying;         
	float fly_timer;
public:
	FlyingFooga(float speed_mult, int extra_hits);


	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float time) override;
	~FlyingFooga();

	//getter ND setters
	bool get_flying();
	float get_fly_timer();
	void set_flying(bool state);
	void set_fly_timer(float time);
};