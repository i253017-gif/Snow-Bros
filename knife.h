#pragma once
#include"Projectile.h"
#include <cmath>

class knife : public Projectile {
private:
	bool is_active;

public:

	knife(float tornado_x, float tornado_y, float player_x, float player_y);  

	//overriden funcs
	void draw(sf::RenderWindow& window) override;
	void update(float time) override;
	void on_hit() override;

	bool getIsActive();  
	void setIsActive(bool state);  

	~knife();
};
