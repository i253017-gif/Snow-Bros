#pragma once
#include"Boss.h"
#include"artillery_rocket.h"

struct RocketData {
	float x, y;
	float vx, vy;
	float blast_radius;
};

class Gamakichi :public Boss {
private:
	float rocket_timer;
	float rocket_spawn_interval;
	int gem_reward;

	// Movement
	float platform_y_position;
	float platform_move_timer;
	float platform_move_speed;
	float platform_min_y;
	float platform_max_y;
	bool moving_up;

public:
	Gamakichi(float x, float y, int hp);
	~Gamakichi();

	void draw(sf::RenderWindow& window) override;
	void move(float delta_time) override;
	void update(float delta_time) override;
	sf::FloatRect getBounds() override;
	std::string get_type() const override;
	void update_attack_phase();

	RocketData* get_rockets_to_spawn(int& count);

	// Getters and setters
	float get_rocket_timer();
	int get_gem_reward();
	void set_rocket_timer(float time);
	void set_gem_reward(int reward);
	float get_rocket_spawn_interval();

	float get_platform_y();
	void set_platform_y(float y);
};