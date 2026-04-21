#include"Mogera.h"
Mogera::Mogera(float x, float y, int hp) :Boss(x, y, 0, hp, 0) {
	if (tex.loadFromFile("assets/Mogera.png")) {
		visual.setTexture(tex);
	}
	child_timer = 4.5f;
	gem_reward = 150;
}
void Mogera::draw(sf::RenderWindow& window) {
	visual.setPosition(pos_x, pos_y);
	window.draw(visual);
}
void Mogera::move(float delta_time) {}
void Mogera::update(float delta_time) {}

Mogera::~Mogera() {}

//setters and fetters

float Mogera::get_child_timer() {
	return child_timer;
}
int Mogera::get_gem_reward() {
	return gem_reward;
}
void Mogera::set_child_timer(float time) {
	child_timer = time;
}
void Mogera::set_gem_reward(int reward) {
	gem_reward = reward;
}
