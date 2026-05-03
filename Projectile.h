#pragma once
#include <SFML/Graphics.hpp>


//it conists from all the thowing mechanism, all the projectiles that the player can throw will be inherited from this class
class Projectile {

protected:
    sf::RectangleShape shape;
    sf::Sprite visual;
    sf::Texture text;
    //positions
    float   pos_x, pos_y;
    //velocities
    float   vel_x, vel_y;
    //damage experienced by the enemy
    int     damage;
    //tells if the projectile hit smth or not
    bool    is_moving;
	sf::FloatRect hitbox; //for collision detection
public:
    Projectile(float x, float y, float vx, float vy, int d);

    virtual ~Projectile();

    //virtual functions 
    virtual void update(float time) = 0;//used to update position of projectile
    virtual void draw(sf::RenderWindow& window) = 0;//used for drawing
    virtual void on_hit() = 0;//tells what happens when projectile hitd smth

    // Setters and Getters

    void set_pos_x(float x);
    void set_pos_y(float y);
    void set_vel_x(float vx);
    void set_vel_y(float vy);
    void set_is_moving(bool state);

    float   get_pos_x();
    float   get_pos_y();
    float   get_vel_x();
    float   get_vel_y();
    int     get_damage();
    bool    get_is_moving();
    sf::FloatRect getBounds();










};