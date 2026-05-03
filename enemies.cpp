#include "Enemy.h"  

/////PURE VIRTUAL FUNCTIONS WONT BE DEFINED IN THIS CLASS THEY WILL BE DEFINED IN THE CHILD CLASSES

//construction initialization
Enemy::Enemy(float hor, float vert, float s, int health, int hit) {
	pos_x = hor;
	pos_y = vert;
	speed = s;
	hp = health;
	snow_hits_needed = hit;
	encased = false;
}

// CHANGED: HP damage only (snow hits handled separately)
void Enemy::take_damage(int amount) {
	hp = hp - amount;
}

// ADDED: snow-only helpers
int Enemy::get_snow_hits_needed() const {
	return snow_hits_needed;
}

void Enemy::set_snow_hits_needed(int hits) {
	snow_hits_needed = hits;
	if (snow_hits_needed <= 0) {
		encased = true;
	}
}

void Enemy::apply_snow_hit(int amount) {
	snow_hits_needed = snow_hits_needed - amount;
	if (snow_hits_needed <= 0) {
		encased = true;
	}
}

//GETTERS
float Enemy::get_pos_x()
{
	return pos_x;
}

float Enemy::get_pos_y() {
	return pos_y;
}
int  Enemy::get_hp() {
	return hp;
}
float Enemy::get_speed() {
	return speed;
}
bool Enemy::get_encased()
{
	return encased;
}

//SETTERS
void Enemy::set_pos_x(float x) {
	pos_x = x;
}
void Enemy::set_pos_y(float y) {
	pos_y = y;
}
void Enemy::set_speed(float s) {
	speed = s;
}
void Enemy::set_encased(bool state) {
	encased = state;
}

Enemy::~Enemy() {
}

void Enemy::setOnGround(bool ground) {
	isOnGround = ground;
}
void Enemy::setVelocity(float v) {
	velocityY = v;
}

float Enemy::getVelocity() {
	return velocityY;
}

void Enemy::newPosition(float x, float y) {
	shape.setPosition(x, y);
	visual.setPosition(shape.getPosition());
}