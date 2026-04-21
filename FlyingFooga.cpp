#include"FlyingFooga.h"
FlyingFooga::FlyingFooga(float speed_mult, int extra_hits) :Botom(speed_mult, extra_hits) {
    if (tex.loadFromFile("assets/FlyingFooga_red.png")) {
        visual.setTexture(tex);
    }



}

void FlyingFooga::draw(sf::RenderWindow& window) {

    visual.setPosition(pos_x, pos_y);
    window.draw(visual);

    this->flying = false;      
    this->fly_timer = 2.5f;    

}

void FlyingFooga::move(float delta_time) {}
void FlyingFooga::update(float time) {}

FlyingFooga::~FlyingFooga() {}



//GETTERS AND SETTERS
void FlyingFooga::set_flying(bool state) {
    flying = state;
}
void FlyingFooga::set_fly_timer(float time) {
    fly_timer = time;

}

bool FlyingFooga::get_flying() {
    return flying;
}
float FlyingFooga::get_fly_timer() {
    return fly_timer;
}