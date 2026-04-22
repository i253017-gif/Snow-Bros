#include"knife.h"
knife::knife(float x, float y, float vx, float vy) :Projectile(x, y, vx, vy, 1) {

    if (tex.loadFromFile("assets/knife.png")) {
        visual.setTexture(tex);
    }

}
void knife::draw(sf::RenderWindow& window) {
    visual.setPosition(pos_x, pos_y);
    window.draw(visual);
}


//ABIHA ADD HOW THE KNIFE IS GONNA MOVE
void knife::update(float delta_time) {

}

// ADD LOGIC FOR WHATS GONNA HAPOPEN WHEN KNIFE HITS
void knife::on_hit() {

}

knife::~knife() {}