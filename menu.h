#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "gamestate.h"
#include "statemachinee.h"
#include "inputmanager.h"
#include "DB_manager.h"

class menu : public gameState {
private:
    stateMachine* machine;
    sf::Font      font;
    sf::Texture   bg_texture;
    sf::Sprite    bg_sprite;
    sf::RectangleShape button[5];
    sf::Text      button_text[5];
    std::string   button_name[5] = {
        "New Game", "Continue", "Leaderboard", "Select Level", "Exit"
    };
    // CHANGED: added username and db
    std::string username;
    DB_manager  db;

public:
    // CHANGED: takes username
    menu(stateMachine* m, std::string logged_in_user = "");
    ~menu() {}
    void handleInput(inputManager& input) override {}
    void update() override {}
    void render(sf::RenderWindow& window) override;
    void handle_mouse_click(sf::Vector2f mouse_pos) override;
    void handle_text_input(sf::Uint32 character) override {}
};