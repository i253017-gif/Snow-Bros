#include"Gamachiki.h"

Gamakichi::Gamakichi(float x, float y, int hp) :Boss(x, y, hp, hp)
{
	type = GAMAKICHI;
	shape.setSize(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(x, y);
	if (text.loadFromFile("assets/Gamakichi.png"))
	{
		visual.setTexture(text);
		visual.setPosition(shape.getPosition());
	}

	pos_x = x;
	pos_y = y;

	rocket_timer = 0.0f;
	rocket_spawn_interval = 3.0f;
	gem_reward = 1000;

	// Platform movement
	platform_y_position = y;
	platform_move_timer = 0.0f;
	platform_move_speed = 0.5f;
	platform_min_y = 100.0f;
	platform_max_y = 500.0f;
	moving_up = false;
}

void Gamakichi::draw(sf::RenderWindow& window) {
	//visual.setPosition(pos_x, pos_y);
	//window.draw(visual);
	window.draw(shape);
	show_health_bar(window);
}

void Gamakichi::move(float delta_time) {
	if (moving_up) {
		platform_y_position -= platform_move_speed;
		if (platform_y_position <= platform_min_y) {
			moving_up = false;
		}
	}
	else {
		platform_y_position += platform_move_speed;
		if (platform_y_position >= platform_max_y) {
			moving_up = true;
		}
	}

	pos_y = platform_y_position;
}

void Gamakichi::update(float delta_time) {
	update_attack_phase();
	move(delta_time);

	rocket_timer += delta_time;
}

void Gamakichi::update_attack_phase() {
	float hp_percentage = (float)hp / (float)boss_hp;

	if (hp_percentage > 0.65f) {
		attack_phase = 1;
		rocket_spawn_interval = 3.0f;
	}
	else if (hp_percentage > 0.35f) {
		attack_phase = 2;
		rocket_spawn_interval = 2.0f;
	}
	else {
		attack_phase = 3;
		rocket_spawn_interval = 1.0f;
	}
}

RocketData* Gamakichi::get_rockets_to_spawn(int& count) {
	static RocketData rockets[4];
	count = 4;

	float spawn_x = pos_x + visual.getLocalBounds().width / 2;
	float spawn_y = pos_y;

	rockets[0] = { spawn_x, spawn_y, 0.0f, -5.0f, 50.0f };
	rockets[1] = { spawn_x, spawn_y, -2.0f, -4.5f, 50.0f };
	rockets[2] = { spawn_x, spawn_y, 2.0f, -4.5f, 50.0f };
	rockets[3] = { spawn_x, spawn_y, 0.0f, -5.0f, 50.0f };

	return rockets;
}

float Gamakichi::get_rocket_timer() {
	return rocket_timer;
}

int Gamakichi::get_gem_reward() {
	return gem_reward;
}

void Gamakichi::set_rocket_timer(float time) {
	rocket_timer = time;
}

void Gamakichi::set_gem_reward(int reward) {
	gem_reward = reward;
}

float Gamakichi::get_platform_y() {
	return platform_y_position;
}

void Gamakichi::set_platform_y(float y) {
	platform_y_position = y;
	pos_y = platform_y_position;
}
float Gamakichi::get_rocket_spawn_interval() {
	return rocket_spawn_interval;
}

Gamakichi::~Gamakichi() {}

sf::FloatRect Gamakichi::getBounds()
{
	return shape.getGlobalBounds();
}

std::string Gamakichi::get_type() const
{
	return "Gamakichi";
}
