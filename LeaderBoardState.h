#pragma once
#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "statemachinee.h"
#include "inputmanager.h"
#include "DB_manager.h"

class LeaderboardState : public gameState {
private:
    stateMachine* machine;
    DB_manager db;
    sf::Font font;
    sf::Texture bg_tex;
    sf::Sprite  bg_sprite;
    sf::RectangleShape panel;
    sf::Text title_text;
    sf::Text header[5];
    sf::RectangleShape back_button;
    sf::Text back_text;
    // max 10 rows x 5 columns
    sf::Text entry_texts[10][5];
    int entry_count;

    void load_entries();

public:
    LeaderboardState(stateMachine* m);
    ~LeaderboardState() {}
    void handleInput(inputManager& input) override {}
    void update() override {}
    void render(sf::RenderWindow& window) override;
    void handle_mouse_click(sf::Vector2f mouse_pos) override;
    void handle_text_input(sf::Uint32 character) override {}
};