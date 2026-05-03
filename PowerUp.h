#pragma once
#include <SFML/Graphics.hpp>
#include"player.h"
class Player;

class PowerUp {
protected:
    float   pos_x, pos_y;
    float   duration;
    sf::Texture tex;
    sf::Sprite  visual;
public:
    PowerUp(float x, float y);
    ~PowerUp();
    virtual void apply(Player& p) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void expire(Player& p) = 0;
    void set_pos_x(float x);
    void set_pos_y(float y);
    float get_pos_x();
    float get_pos_y();
};