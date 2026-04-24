#include"Tornado.h"
Tornado::Tornado(float x, float y, float speed_mult, int extra_hits):FlyingFooga(x,y,speed_mult, extra_hits) {
    if (tex.loadFromFile("assets/FlyingFooga_red.png")) {
        visual.setTexture(tex);
    }
  
    this->knife_timer = 2.5f;
}

void Tornado::draw(sf::RenderWindow& window) {

    visual.setPosition(pos_x, pos_y);
    window.draw(visual);

    

}

void Tornado::move(float delta_time) {}
void Tornado::update(float time) {}

Tornado::~Tornado() {}



//GETTERS AND SETTERS

void Tornado::set_knife_timer(float time) {
    knife_timer = time;

}

float Tornado::get_knife_timer() {
    return knife_timer;
}