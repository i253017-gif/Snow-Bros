#include"ColorVariant.h"
ColorVariant::ColorVariant(Enemy* parent, int level, std::string e_type): Enemy(parent->get_pos_x(), 
    parent->get_pos_y(), parent->get_speed(), parent->get_hp(), parent->get_snow_hits_needed()) {

    /*ok so we r doing all this cz we cant call a copy contructor outta
    abstract class*/
 enemy_type = e_type;

    //specifying whats gonna be speed mult and extra hits based on levels
    if (level <= 5) {
        speed_multiplier = 1.0f;
        extra_hits = 0;
    }
    else if (level <= 7) {
        speed_multiplier = 1.25f;
        extra_hits = 1;
    }
    else if (level <= 8) {
        speed_multiplier = 1.5f;
        extra_hits = 2;
    }
    else {
        speed_multiplier = 1.75f;
        extra_hits = 3;
    }
    //we will multiply these with our speed and hits needed
    speed *=  speed_multiplier;
    snow_hits_needed +=  extra_hits;


    std::string color_name;

    //file handling would get easier if we js define a path and change name and type accordingly
    std::string file_path = "assets/" + enemy_type + "_" + color_name + ".png";
    if (level <= 5) {
        color_name = "red";
    }
    else if (level <= 7) {
        color_name = "green";
    }
    else if (level <= 8) {
        color_name = "blue";
    }
    else {
        color_name = "purple";
    }


    //hard coding our file paths to make work shorter
    std::string filename;
    if (enemy_type == "Botom") {
        filename = "botom_" + color_name + ".png";
    }
    else if (enemy_type == "FlyingFooga") {
        filename = "flyingfooga_" + color_name + ".png";
    }
    else if (enemy_type == "Tornado") {
        filename = "tornado_" + color_name + ".png";
    }

    //here we are loading the sprites
    tex.loadFromFile("assets/" + filename);
   visual.setTexture(tex);
}
//drawing the sprite loaded
void ColorVariant::draw(sf::RenderWindow& window) {
        visual.setPosition(pos_x, pos_y);
        window.draw(visual);
   
}

//FUNCTIONS TO BE WRITTEN BY ABIHAAAA
void ColorVariant::move(float delta_time) {
    
}

void ColorVariant::update(float delta_time) {
    



}




//SETTERS ND GETTERS

float ColorVariant::get_speed_multiplier() {
    return speed_multiplier; 
}
int ColorVariant::get_extra_hits() {
    return extra_hits;
}

std::string ColorVariant::get_enemy_type() {
    return enemy_type; 
}


void ColorVariant::set_speed_multiplier(float s_m) {
    speed_multiplier = s_m;
}
void ColorVariant::set_extra_hits(int hits) {
    extra_hits = hits;
}

void ColorVariant::set_enemy_type(std::string e_type) {
    enemy_type = e_type;
}

ColorVariant::~ColorVariant(){}