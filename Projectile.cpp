#include "Projectile.h"

/////PURE VIRTUAL FUNCTIONS WONT BE DEFINED IN THIS CLASS THEY WILL BE DEFINED IN THE CHILD CLASSES

Projectile::Projectile(float x, float y, float vx, float vy, int d) {
    pos_x = x;
    pos_y = y;
    vel_x = vx;
    vel_y = vy;
    damage = d;
    is_moving = true;
}


// Getters and setters

float   Projectile::get_pos_x() { 
    return pos_x; 
}
float   Projectile::get_pos_y() {
    return pos_y; 
}
float   Projectile::get_vel_x() {
    return vel_x;
}
float   Projectile::get_vel_y() {
    return vel_y; }
int     Projectile::get_damage() { 
    return damage;
}
bool    Projectile::get_is_moving() { 
    return is_moving; 
}
hit_box Projectile::get_hit_box() { 
    return hitbox; 
}

void Projectile::set_pos_x(float x) {
    pos_x = x; 
}
void Projectile::set_pos_y(float y) {
    pos_y = y; 
}
void Projectile::set_vel_x(float vx) { 
    vel_x = vx;
}
void Projectile::set_vel_y(float vy) {
    vel_y = vy;
}
void Projectile::set_is_moving(bool state) {
    is_moving = state; 
}

Projectile::~Projectile() {}