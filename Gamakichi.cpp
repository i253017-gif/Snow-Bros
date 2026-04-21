#include"Gamakichi.h"
Gamakichi::Gamakichi(float x, float y, int hp) :Boss(x, y, 0, hp, 0) {
	if (tex.loadFromFile("assets/Gamakichi.png")) {
		visual.setTexture(tex);
	}
	rocket_timer = 2.5f;
	gem_reward = 450;
}
void Gamakichi::draw(sf::RenderWindow& window) {
	visual.setPosition(pos_x, pos_y);
	window.draw(visual);
}
void Gamakichi::move(float delta_time){}
void Gamakichi::update(float delta_time){}

Gamakichi::~Gamakichi(){}
//setters nd gtters
float Gamakichi::get_rocket_timer() {
	return rocket_timer;
}
int Gamakichi:: get_gem_reward() {
	return gem_reward;
}
void Gamakichi::set_rocket_timer(float time) {
	rocket_timer = time;
}
void Gamakichi::set_gem_reward(int reward)
{
	gem_reward = reward;
}