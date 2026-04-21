#include"Bottom.h"
Botom::Botom(float speed_mult, int extra_hits) :Enemy(0.0, 0.0, 75.0f * speed_mult, 10, 5 + extra_hits) {
    if (tex.loadFromFile("assets/botom_red.png")) {
        visual.setTexture(tex);
    }



}

void Botom::draw(sf::RenderWindow& window) {

    visual.setPosition(pos_x, pos_y);
    window.draw(visual);


}

void Botom::move(float delta_time) {} 
void Botom::update(float time){}

Botom::~Botom() {}