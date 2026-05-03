#include "RegisterState.h"
#include "LoginState.h"
#include "menu.h"

RegisterState::RegisterState(stateMachine* m) : machine(m) {
    username_active = false;
    password_active = false;
    email_active = false;
    message = "";
    is_error = false;

    // CHANGED: fixed font path
    font.loadFromFile("arial.ttf");

    bg_tex.loadFromFile("images/bg.png");
    bg_sprite.setTexture(bg_tex);
    bg_sprite.setScale(700.f / bg_tex.getSize().x, 700.f / bg_tex.getSize().y);

    sisters_tex.loadFromFile("images/snowsisters.png");
    sisters_sprite.setTexture(sisters_tex);
    sisters_sprite.setScale(1.0f, 1.0f);
    sisters_sprite.setPosition(-85, -230);

    enemies_tex.loadFromFile("images/enemies.png");
    enemies_sprite.setTexture(enemies_tex);
    enemies_sprite.setScale(0.5f, 0.5f);
    enemies_sprite.setPosition(500, 510);

    screen.setSize(sf::Vector2f(320, 500));
    screen.setPosition(190, 100);
    screen.setFillColor(sf::Color(0, 0, 0, 160));

    title_text.setFont(font);
    title_text.setString("SNOW BROS");
    title_text.setCharacterSize(40);
    title_text.setFillColor(sf::Color::White);
    title_text.setStyle(sf::Text::Bold);
    title_text.setPosition(215, 115);

    username_label.setFont(font);
    username_label.setString("Username");
    username_label.setCharacterSize(13);
    username_label.setFillColor(sf::Color(200, 220, 255));
    username_label.setPosition(210, 200);
    username_line.setSize(sf::Vector2f(280, 1));
    username_line.setPosition(210, 228);
    username_line.setFillColor(sf::Color(200, 220, 255));
    username_display.setFont(font);
    username_display.setCharacterSize(15);
    username_display.setFillColor(sf::Color::White);
    username_display.setPosition(210, 210);

    password_label.setFont(font);
    password_label.setString("Password");
    password_label.setCharacterSize(13);
    password_label.setFillColor(sf::Color(200, 220, 255));
    password_label.setPosition(210, 250);
    password_line.setSize(sf::Vector2f(280, 1));
    password_line.setPosition(210, 278);
    password_line.setFillColor(sf::Color(200, 220, 255));
    password_display.setFont(font);
    password_display.setCharacterSize(15);
    password_display.setFillColor(sf::Color::White);
    password_display.setPosition(210, 260);

    email_label.setFont(font);
    email_label.setString("Email (optional)");
    email_label.setCharacterSize(13);
    email_label.setFillColor(sf::Color(200, 220, 255));
    email_label.setPosition(210, 300);
    email_line.setSize(sf::Vector2f(280, 1));
    email_line.setPosition(210, 328);
    email_line.setFillColor(sf::Color(200, 220, 255));
    email_display.setFont(font);
    email_display.setCharacterSize(15);
    email_display.setFillColor(sf::Color::White);
    email_display.setPosition(210, 310);

    register_button.setSize(sf::Vector2f(280, 45));
    register_button.setPosition(210, 360);
    register_button.setFillColor(sf::Color(100, 180, 255));
    register_button_text.setFont(font);
    register_button_text.setString("Register");
    register_button_text.setCharacterSize(18);
    register_button_text.setFillColor(sf::Color::White);
    register_button_text.setStyle(sf::Text::Bold);
    register_button_text.setPosition(305, 370);

    login_link.setFont(font);
    login_link.setString("Already have an account? Login");
    login_link.setCharacterSize(13);
    login_link.setFillColor(sf::Color(150, 200, 255));
    login_link.setPosition(210, 425);

    message_text.setFont(font);
    message_text.setCharacterSize(13);
    message_text.setPosition(210, 460);
}

void RegisterState::handleInput(inputManager& input) {}
void RegisterState::update() {}

void RegisterState::handle_text_input(sf::Uint32 character) {
    if (character == 8) {
        if (username_active && !username_input.empty())
            username_input.pop_back();
        if (password_active && !password_input.empty())
            password_input.pop_back();
        if (email_active && !email_input.empty())
            email_input.pop_back();
    }
    else if (character >= 32 && character < 128) {
        if (username_active && username_input.size() < 20)
            username_input += (char)character;
        if (password_active && password_input.size() < 20)
            password_input += (char)character;
        if (email_active && email_input.size() < 40)
            email_input += (char)character;
    }
    username_display.setString(username_input);
    password_display.setString(std::string(password_input.size(), '*'));
    email_display.setString(email_input);
}

void RegisterState::handle_mouse_click(sf::Vector2f mp) {
    username_active = username_line.getGlobalBounds().contains(mp) ||
        username_label.getGlobalBounds().contains(mp);
    password_active = password_line.getGlobalBounds().contains(mp) ||
        password_label.getGlobalBounds().contains(mp);
    email_active = email_line.getGlobalBounds().contains(mp) ||
        email_label.getGlobalBounds().contains(mp);

    username_line.setFillColor(username_active ? sf::Color::White : sf::Color(200, 220, 255));
    password_line.setFillColor(password_active ? sf::Color::White : sf::Color(200, 220, 255));
    email_line.setFillColor(email_active ? sf::Color::White : sf::Color(200, 220, 255));

    if (register_button.getGlobalBounds().contains(mp)) {
        if (username_input.empty() || password_input.empty()) {
            message = "Username and password required!";
            is_error = true;
        }
        else if (login_mgr.register_user(username_input, password_input, email_input)) {
            // CHANGED: pass username to menu
            machine->changeState(new menu(machine, login_mgr.get_current_user()));
            return;
        }
        else {
            message = "Username already taken!";
            is_error = true;
        }
        message_text.setString(message);
        message_text.setFillColor(is_error ? sf::Color(255, 100, 100) : sf::Color(100, 255, 100));
    }

    if (login_link.getGlobalBounds().contains(mp))
        machine->changeState(new LoginState(machine));
}

void RegisterState::render(sf::RenderWindow& window) {
    window.draw(bg_sprite);
    window.draw(sisters_sprite);
    window.draw(enemies_sprite);
    window.draw(screen);
    window.draw(title_text);
    window.draw(username_label);
    window.draw(username_line);
    window.draw(username_display);
    window.draw(password_label);
    window.draw(password_line);
    window.draw(password_display);
    window.draw(email_label);
    window.draw(email_line);
    window.draw(email_display);
    window.draw(register_button);
    window.draw(register_button_text);
    window.draw(login_link);
    if (!message.empty()) window.draw(message_text);
}