#include "PowerUp.h"

/////PURE VIRTUAL FUNCTIONS WONT BE DEFINED IN THIS CLASS THEY WILL BE DEFINED IN THE CHILD CLASSES

//constructo initialization

PowerUp::PowerUp(float x, float y) {
	pos_x = x;
	pos_y = y;

}

//SETTERS AND GETTERS


float PowerUp::get_pos_x() {
	return pos_x;
}
float PowerUp::get_pos_y() {
	return pos_y;
}

hit_box PowerUp::get_hit_box() {
	return hitbox;
}

void PowerUp::set_pos_x(float x) {
	pos_x = x;
}
void PowerUp::set_pos_y(float y) {
	pos_y = y;
}


PowerUp::~PowerUp() {}