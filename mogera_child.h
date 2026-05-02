#pragma once
#include"Enemy.h"
class Mogera_child :public Enemy {
	float dir_x, dir_y; // fixed movement direction (-1=left, 1=right)
	bool isGravityOn;
	float initialSpeed;   //before gravity gets applied

	float throwTimer;       // Time before gravity applies
	float THROW_DELAY = 0.5f;  // 0.3 seconds before gravity
public:
	Mogera_child(float x, float y, float dx, float dy);
	~Mogera_child();

	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float time) override;
	sf::FloatRect getBounds() override;
	std::string get_type() const override;

	float get_dir_x();
	void set_dir_x(float x);
	float get_dir_y();
	void set_dir_y(float y);










};
