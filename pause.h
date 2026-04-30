
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "gamestate.h"
#include "statemachinee.h"
#include "inputmanager.h"
//inherits from gameState, so we can use it in our state machine
class pause : public gameState
{
    stateMachine* machine;
    sf::Font      font;

    // background
    sf::Texture bg_texture;
    sf::Sprite  bg_sprite;

    //2  buttons left side
    sf::RectangleShape button[2];
    sf::Text button_text[2];
    std::string button_name[2] = { "Resume", "Save"};

    //2 buttons right side
        sf::RectangleShape button_2[2];
        sf::Text           button_text2[2];
        std::string        button_name2[2] = {  "Shop",  "Logout"  };

        //1 button bottom centre
        sf::RectangleShape button3;
        sf:: Text button_text3;
        std::string button_name3 = "Exit to Main Menu";

public:
    pause(stateMachine* m);
    ~pause() {}
    void handleInput(inputManager& input) override {}
    void update() override {}
    void render(sf::RenderWindow& window) override;
    void handle_mouse_click(sf::Vector2f mouse_pos) override;
    void handle_text_input(sf::Uint32 character) override {}
};