
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
void Enemy::take_damage(int amount) {
	hp = hp - amount;
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
		hit_box Enemy::get_hit_box() {
			return hitbox;
		}

		//SETTERS
		int Enemy::get_snow_hits_needed() {
			return snow_hits_needed;
		}

		void Enemy::set_snow_hits_needed(int hits) {
			snow_hits_needed = hits;
		}
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