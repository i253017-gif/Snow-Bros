#include "LoginState.h"
#include "RegisterState.h"
#include "menustate.h"

// ============================================================
// LoginState.cpp
// Written by: Ishmal (Student B)
// ============================================================

LoginState::LoginState(stateMachine* m) : machine(m) {
    username_active = false;
    password_active = false;
    error_message = "";

    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    // background
    bg_tex.loadFromFile("images/bg.png");
    bg_sprite.setTexture(bg_tex);
    bg_sprite.setScale(700.f / bg_tex.getSize().x, 700.f / bg_tex.getSize().y);

    // snow sisters bottom left
    sisters_tex.loadFromFile("images/snowsisters.png");
    sisters_sprite.setTexture(sisters_tex);
    sisters_sprite.setScale(1.0f, 1.0f);
    sisters_sprite.setPosition(-85, -230);

    // enemies bottom right
    enemies_tex.loadFromFile("images/enemies.png");
    enemies_sprite.setTexture(enemies_tex);
    enemies_sprite.setScale(0.5f, 0.5f);
    enemies_sprite.setPosition(500, 510);

    // dark glass panel
    panel.setSize(sf::Vector2f(320, 420));
    panel.setPosition(190, 140);
    panel.setFillColor(sf::Color(0, 0, 0, 160));
    panel.setOutlineColor(sf::Color(255, 255, 255, 60));
    panel.setOutlineThickness(1);

    // title
    title_text.setFont(font);
    title_text.setString("SNOW BROS");
    title_text.setCharacterSize(40);
    title_text.setFillColor(sf::Color::White);
    title_text.setStyle(sf::Text::Bold);
    title_text.setPosition(215, 155);

    // username
    username_label.setFont(font);
    username_label.setString("Username");
    username_label.setCharacterSize(13);
    username_label.setFillColor(sf::Color(200, 220, 255));
    username_label.setPosition(210, 245);

    username_line.setSize(sf::Vector2f(280, 1));
    username_line.setPosition(210, 273);
    username_line.setFillColor(sf::Color(200, 220, 255));

    username_display.setFont(font);
    username_display.setCharacterSize(15);
    username_display.setFillColor(sf::Color::White);
    username_display.setPosition(210, 255);

    // password
    password_label.setFont(font);
    password_label.setString("Password");
    password_label.setCharacterSize(13);
    password_label.setFillColor(sf::Color(200, 220, 255));
    password_label.setPosition(210, 300);

    password_line.setSize(sf::Vector2f(280, 1));
    password_line.setPosition(210, 328);
    password_line.setFillColor(sf::Color(200, 220, 255));

    password_display.setFont(font);
    password_display.setCharacterSize(15);
    password_display.setFillColor(sf::Color::White);
    password_display.setPosition(210, 310);

    // login button
    login_btn.setSize(sf::Vector2f(280, 45));
    login_btn.setPosition(210, 365);
    login_btn.setFillColor(sf::Color(100, 180, 255));

    login_btn_text.setFont(font);
    login_btn_text.setString("Login");
    login_btn_text.setCharacterSize(18);
    login_btn_text.setFillColor(sf::Color::White);
    login_btn_text.setStyle(sf::Text::Bold);
    login_btn_text.setPosition(325, 375);

    // register link
    register_link.setFont(font);
    register_link.setString("Don't have an account? Register");
    register_link.setCharacterSize(13);
    register_link.setFillColor(sf::Color(150, 200, 255));
    register_link.setPosition(210, 428);

    // error text
    error_text.setFont(font);
    error_text.setCharacterSize(13);
    error_text.setFillColor(sf::Color(255, 100, 100));
    error_text.setPosition(210, 460);
}

void LoginState::handleInput(inputManager& input) {
    // keyboard input handled via events in Gameloop
}

void LoginState::update() {
    // nothing to update every frame
}

void LoginState::handle_text_input(sf::Uint32 character) {
    if (character == 8) {
        if (username_active && !username_input.empty()) username_input.pop_back();
        if (password_active && !password_input.empty()) password_input.pop_back();
    }
    else if (character >= 32 && character < 128) {
        if (username_active && username_input.size() < 20)
            username_input += (char)character;
        if (password_active && password_input.size() < 20)
            password_input += (char)character;
    }
    username_display.setString(username_input);
    password_display.setString(std::string(password_input.size(), '*'));
}

void LoginState::handle_mouse_click(sf::Vector2f mp) {
    // activate field on click
    username_active = username_line.getGlobalBounds().contains(mp) ||
        username_label.getGlobalBounds().contains(mp);
    password_active = password_line.getGlobalBounds().contains(mp) ||
        password_label.getGlobalBounds().contains(mp);

    // highlight active line
    username_line.setFillColor(username_active ? sf::Color::White : sf::Color(200, 220, 255));
    password_line.setFillColor(password_active ? sf::Color::White : sf::Color(200, 220, 255));

    // login button
    if (login_btn.getGlobalBounds().contains(mp)) {
        if (username_input.empty() || password_input.empty()) {
            error_message = "Please enter username and password!";
        }
        else if (login_mgr.login(username_input, password_input)) {
            machine->changeState(new menuState(machine));
            return;
        }
        else {
            error_message = "Wrong username or password!";
        }
        error_text.setString(error_message);
    }

    // register link
    if (register_link.getGlobalBounds().contains(mp)) {
        machine->changeState(new RegisterState(machine));
    }
}

void LoginState::render(sf::RenderWindow& window) {
    window.draw(bg_sprite);
    window.draw(sisters_sprite);
    window.draw(enemies_sprite);
    window.draw(panel);
    window.draw(title_text);
    window.draw(username_label);
    window.draw(username_line);
    window.draw(username_display);
    window.draw(password_label);
    window.draw(password_line);
    window.draw(password_display);
    window.draw(login_btn);
    window.draw(login_btn_text);
    window.draw(register_link);
    if (!error_message.empty()) window.draw(error_text);
}