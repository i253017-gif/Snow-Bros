#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "PowerUp_funcs.h"

class StarEvent {

private:
    sf::Texture    star_texture;//these are used to show star icon on screem
    sf::Sprite     star_sprite;
    bool           star_loaded;
    float          star_x, star_y;   // spawning position
    bool           star_collected;   // if player collected it or not
    bool           star_inaffect;      // the effect

    bool showing_types;  // show choices on screen or not
    std::string types[3];//3 random power up types
    ////buttons for selextion of sprite
    sf::RectangleShape button[3];
    sf::Sprite button_icons[3];
    sf::Texture button_tex[3];
    sf::Text button_labels[3];
    sf::Text title_text;
    // the bg of buttons will be transparent
    sf::RectangleShape overlay;
    sf::RectangleShape panel;
    sf::Font font;

    // ADDED: stores chosen type so playState can apply/track it
    std::string chosen_type;

    // for generating powerupos
    void generate_types();
public:
    StarEvent();
    void spawn_star(float x, float y);
    void check_collection(sf::FloatRect player_bounds);
    void draw_star(sf::RenderWindow& window);
    void draw_types(sf::RenderWindow& window);
    void handle_click(sf::Vector2f mouse_pos, Player& player);

    // ADDED: playState reads choice and applies it (no stacking + lasts till level end)
    std::string consume_chosen_type();

    // getters
    bool get_showing_types();
    bool get_star_inaffect();
    bool get_star_collected();
};