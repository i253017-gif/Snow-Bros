#pragma once
#include"Projectile.h"
class artillery_rocket :public Projectile {

private:
	float blast_radius;



public:
	artillery_rocket(float x, float y, float vx, float vy, float rad);


	//overriden funcs
	void draw(sf::RenderWindow& window) override;
	void update(float time) override;
	void on_hit() override;

	~artillery_rocket() {}

	//setters getters
	float get_blast_radius();
	void set_blast_radius(float rad);




};