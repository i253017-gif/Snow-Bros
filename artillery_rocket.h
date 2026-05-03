#pragma once
#include"Projectile.h"

class artillery_rocket :public Projectile {

private:
	float blast_radius;
	bool has_exploded;
	float explosion_timer;
	float explosion_duration;
	float velocityX;
	float velocityY;

public:
	artillery_rocket(float x, float y, float vx, float vy, float rad);

	void draw(sf::RenderWindow& window) override;
	void move(float delta_time);
	void update(float delta_time) override;
	void on_hit() override;

	~artillery_rocket();

	float get_blast_radius();
	void set_blast_radius(float rad);

	bool get_has_exploded();
	void set_has_exploded(bool exploded);

	sf::FloatRect getBounds();
};