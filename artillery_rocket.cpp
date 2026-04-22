#include"artillery_rocket.h"
artillery_rocket::artillery_rocket(float x, float y, float vx, float vy, float rad) :Projectile(x, y, vx, vy, 1) {
    blast_radius = rad;
    if (tex.loadFromFile("assets/artillery_rocket.png")) {
        visual.setTexture(tex);
    }

}
void artillery_rocket::draw(sf::RenderWindow& window) {
    visual.setPosition(pos_x, pos_y);
    window.draw(visual);
}


//ABIHA ADD HOW THE rocket IS GONNA MOVE
void artillery_rocket::update(float delta_time) {

}

// ADD LOGIC FOR WHATS GONNA HAPOPEN WHEN KNIFE HITS
void artillery_rocket::on_hit() {

}

artillery_rocket::~artillery_rocket() {}

//getter setter
float artillery_rocket::get_blast_radius() {
    return blast_radius; 
}
void artillery_rocket::set_blast_radius(float rad) { 
    blast_radius=rad;
}