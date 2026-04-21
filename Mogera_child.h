#pragma once
#include"Enemy.h"
class Mogera_child:public Enemy{ 
	float dir_x, dir_y; //hor and vert dirctions
public:
	Mogera_child(float x, float y, float dx, float dy);
	~Mogera_child() {};

	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float time) override;

	float get_dir_x();
	void set_dir_x(float x);
	float get_dir_y();
	void set_dir_y(int y);










};