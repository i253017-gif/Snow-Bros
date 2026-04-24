#include"FlyingFooga.h"
FlyingFooga::FlyingFooga(float x, float y, float speed_mult, int extra_hits) :Botom(x, y,speed_mult, extra_hits) {
    if (tex.loadFromFile("assets/FlyingFooga_red.png")) {
        visual.setTexture(tex);
    }


    flying = false;
    fly_timer = 2.5f;

}

void FlyingFooga::draw(sf::RenderWindow& window) {

    visual.setPosition(pos_x, pos_y);
    window.draw(visual);


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