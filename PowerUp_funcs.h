#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "player.h"

// Represents a single power-up: either a floor pickup or a star-chosen award.
// Types: "speed" (15s), "balloon" (10s), "snowball"/"distance" (until level end).
// fromStar = true forces timer = -1 (lasts until level end regardless of type).
class PowerUp_funcs
{
private:
    std::string type;   // "speed", "snowball", "distance", "balloon"
    float pos_x;
    float pos_y;
    float timer;        // seconds remaining; -1 = permanent until level end
    bool  fromStar;

    sf::RectangleShape visual;
    sf::Texture        texture;
    bool               texLoaded;

public:
    // x, y = position on floor (0,0 is fine for star-chosen pick-ups)
    // fromStar = true makes this power-up last until level end
    PowerUp_funcs(const std::string& t, float x, float y, bool fromStar);

    void apply (Player& player);
    void expire(Player& player);
    void update(float dt);              // decrements timer
    void draw  (sf::RenderWindow& window);

    float       get_timer()   const;
    float       get_pos_x()   const;
    float       get_pos_y()   const;
    std::string get_type()    const;
};
