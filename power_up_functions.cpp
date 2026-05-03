#include"PowerUp_funcs.h"
#include"player.h"

PowerUp_funcs::PowerUp_funcs(std::string type, float x, float y, bool from_star) :PowerUp(x, y) {
    powerup_type = type;
    //setting how long theeffect will last
    if (from_star) {
        timer = -1.0f;
    }
    else if (type == "speed") {
        timer = 15.0f;
    }
    else if (type == "balloon") {
        timer = 10.0f;
    }
    else  if (type == "snowball") {
        timer = -1.0f;
    }
    else if (type == "distance") {
        timer = -1.0f;
    }

    // decisiding which sprite should be loaded
    std::string image = "";
    if (type == "speed") {
        image = "images/speed.jpeg";
    }
    else if (type == "snowball") {
        image = "images/snowpower.jpeg";
    }
    else if (type == "distance") {
        image = "images/distance.jpeg";
    }
    else if (type == "balloon") {
        image = "images/balloon.jpeg";
    }
    if (tex.loadFromFile(image)) {
        visual.setTexture(tex);
        float scale = 30.f / tex.getSize().x;
        visual.setScale(scale, scale);
    }
}

void PowerUp_funcs::apply(Player& p) {
    if (powerup_type == "speed") {
        apply_speed(p);
    }
    else if (powerup_type == "snowball") {
        apply_snowball(p);
    }
    else if (powerup_type == "distance") {
        apply_distance(p);
    }
    else if (powerup_type == "balloon") {
        apply_balloon(p);
    }
}

// CHANGED: store original speed so we can restore (no stacking issues)
void PowerUp_funcs::apply_speed(Player& p) {
    original_speed = p.get_speed();
    p.set_speed(original_speed * 1.5f);
}

void PowerUp_funcs::apply_snowball(Player& p) {
    p.set_snowball_power(true);
}

void PowerUp_funcs::apply_distance(Player& p) {
    original_distance = p.get_snowball_distance();
    p.set_snowball_distance(700.f);
}

void PowerUp_funcs::apply_balloon(Player& p) {
    p.set_balloon_mode(true);
}

void PowerUp_funcs::expire(Player& p) {
    if (powerup_type == "speed") {
        p.set_speed(original_speed); // CHANGED
    }
    if (powerup_type == "snowball") {
        p.set_snowball_power(false);
    }
    if (powerup_type == "distance") {
        p.set_snowball_distance(original_distance);
    }
    if (powerup_type == "balloon") {
        p.set_balloon_mode(false);
    }
}

void PowerUp_funcs::update(float delta_time) {
    if (timer > 0)   // only count down if not level-end type
        timer -= delta_time;
}

void PowerUp_funcs::draw(sf::RenderWindow& window) {
    {
        visual.setPosition(pos_x, pos_y);
        window.draw(visual);
    }
}

// Getters
std::string PowerUp_funcs::get_powerup_type() {
    return powerup_type;
}
float   PowerUp_funcs::get_timer() {
    return timer;
}

PowerUp_funcs::~PowerUp_funcs() {}