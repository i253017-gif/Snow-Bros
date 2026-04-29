#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "gamestate.h"
#include "statemachinee.h"
#include "inputmanager.h"
#include "Login_manager.h"

// ============================================================
// LoginState.h
// Login screen - accessed from register screen
// Written by: Ishmal (Student B)
// Spec ref: Section 10.1
// ============================================================

class LoginState : public gameState {
private:
    stateMachine* machine;
    Login_manager login_mgr;
    sf::Font      font;

    // background + sprites
    sf::Texture        bg_tex;
    sf::Sprite         bg_sprite;
    sf::Texture        sisters_tex;
    sf::Sprite         sisters_sprite;
    sf::Texture        enemies_tex;
    sf::Sprite         enemies_sprite;

    // glass panel
    sf::RectangleShape panel;
    sf::Text           title_text;

    // username field
    sf::RectangleShape username_line;
    sf::Text           username_label;
    sf::Text           username_display;
    std::string        username_input;
    bool               username_active;

    // password field
    sf::RectangleShape password_line;
    sf::Text           password_label;
    sf::Text           password_display;
    std::string        password_input;
    bool               password_active;

    // button + links
    sf::RectangleShape login_btn;
    sf::Text           login_btn_text;
    sf::Text           register_link;
    sf::Text           error_text;
    std::string        error_message;

public:
    LoginState(stateMachine* m);
    ~LoginState() {}

    // matches Abiha's gameState exactly
    void handleInput(inputManager& input) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

    // called from Gameloop event loop
    void handle_text_input(sf::Uint32 character);
    void handle_mouse_click(sf::Vector2f mouse_pos);
};