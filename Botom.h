#pragma once
#include "Enemy.h"
class Botom :public Enemy {
protected:


	
	float gravity;
	
	int direction;
	float directionTimer;   //helps change enemy direction and acts as a timer
	float directionChange; //how long enemy moves in one direction or like how often the direction changes
public:
	Botom();
	Botom(float x, float y, float speed_mult, int extra_hits);


	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float time) override;
	 sf::FloatRect getBounds() override;

	

	
	~Botom();
};
