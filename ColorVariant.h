#pragma once
#include"Enemy.h"
class ColorVariant :public Enemy {
protected:
    float        speed_multiplier;  
    int          extra_hits;            
    std::string  enemy_type;       
public:
    ColorVariant(Enemy* parent, int level, std::string e_type);

   /*this constructor helps make a variant of the org enemy 
    and the pointer would help us extract feature sfrom the org enmy
   */
    //we need to do this cz we cant use a copy constructor as enemy class is abstract



    //overridden functions from enemy:
    void draw(sf::RenderWindow& window) override;
    void update(float delta_time) override;
    void move(float delta_time) override;

    //setter gettetrsrss

    float get_speed_multiplier();
    int  get_extra_hits();
    std::string  get_enemy_type();


    void  set_speed_multiplier(float s_m);
    void  set_extra_hits(int hits);
    void set_enemy_type(std::string type);


  ~ColorVariant();










};
