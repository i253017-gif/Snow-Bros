#include"Mogera_child.h"
Mogera_child::Mogera_child(float x, float y, float dx, float dy) :Enemy(x, y, 75.0f, 1, 1) {

	if (tex.loadFromFile("assets/mogera_child.png")) {
		visual.setTexture(tex);
	}

	dir_x = dx;
	dir_y = dy;


}

void Mogera_child::draw(sf::RenderWindow& window) {

	visual.setPosition(pos_x, pos_y);
	window.draw(visual);


}

void Mogera_child::move(float delta_time) {}
void Mogera_child::update(float time) {}

float  Mogera_child::get_dir_x() {
	return dir_x;

}
void  Mogera_child::set_dir_x(float x) {
	dir_x = x;
}
float Mogera_child::get_dir_y() {
	return dir_y;

}
void  Mogera_child::set_dir_y(float y) {

	dir_y = y;
}
Mogera_child::~Mogera_child(){}