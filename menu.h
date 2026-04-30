#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "gamestate.h"
#include "statemachinee.h"
#include "inputmanager.h"
//inherit from gameState and implement menu state
class menu : public gameState {
private:
    stateMachine* machine;
    sf::Font      font;
    // background
    sf::Texture bg_texture;
    sf::Sprite  bg_sprite;

    // 6 buttons - right side
    sf::RectangleShape button[5];
    sf::Text button_text[5];
    std::string button_name[5] = { "New Game","Continue",  "Leaderboard","Select Level", "Exit"
    };

public:
    menu(stateMachine* m);
    ~menu() {}
    void handleInput(inputManager& input) override {}
    void update() override {}
    void render(sf::RenderWindow& window) override;
    void handle_mouse_click(sf::Vector2f mouse_pos) override;
    void handle_text_input(sf::Uint32 character) override {}
};