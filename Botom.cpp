#include"Bottom.h"
Botom::Botom(float x, float y, float speed_mult, int extra_hits):Enemy(x, y, 75.0f * speed_mult, 1, 1 + extra_hits) {
    if (tex.loadFromFile("assets/botom_red.png")) {
        visual.setTexture(tex);
    }



}

void Botom::draw(sf::RenderWindow& window) {

    visual.setPosition(pos_x, pos_y);
    window.draw(visual);


}

void Botom::move(float delta_time) {}
void Botom::update(float time) {}

Botom::~Botom() {}