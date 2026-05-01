#pragma once
#include <SFML/Graphics.hpp> 
#include"player.h"
class Player;

class PowerUp {
protected:
    //positions
    float   pos_x, pos_y;
    //duration the effect is gonna stau for
    float   duration;
    sf::Texture tex;
    sf::Sprite  visual;

public:

    //constructor
    PowerUp(float x, float y);
    ~PowerUp();
    //pure virtual funcs which make the class abstract

    virtual void apply(Player& p) = 0; //apply the effect to the player
    virtual void draw(sf::RenderWindow& window) = 0;//drawing powerups
    virtual void expire(Player& p) = 0;//the duration of powerup ends so the effect needs to be removed

    //GETTERS AND SETTERS



    void set_pos_x(float x);
    void set_pos_y(float y);


    float   get_pos_x();
    float   get_pos_y();
};