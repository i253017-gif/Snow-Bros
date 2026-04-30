#include "menu.h"

menu::menu(stateMachine* m) : machine(m) {
 font.loadFromFile("C:/Windows/Fonts/arial.ttf");
// background
    bg_texture.loadFromFile("images/background.png");
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setScale(  700.f / bg_texture.getSize().x,   700.f / bg_texture.getSize().y );
// --- 6 buttons on right side ---
    float button_x = 420;   // x position of buttons
    float button_y = 280;   // starting y position
    float button_width = 230;   // button width
    float button_height = 50;    // button height
    float button_gap = 70;    // gap between buttons
for (int i = 0; i < 5; i++) {
        // button box - dark orange
    button[i].setSize(sf::Vector2f(button_width, button_height));
    button[i].setPosition(button_x, button_y + (i * button_gap));
        button[i].setFillColor(sf::Color(180, 80, 0));         // dark orange
 // button text - white
        button_text[i].setFont(font);
        button_text[i].setString(button_name[i]);
        button_text[i].setCharacterSize(20);
        button_text[i].setFillColor(sf::Color::White);
        button_text[i].setStyle(sf::Text::Bold);
        // center text inside button
        float text_x = button_x + (button_width / 2) - (button_text[i].getGlobalBounds().width / 2);
        float text_y = button_y + (i * button_gap) + (button_height / 2) - 12;
        button_text[i].setPosition(text_x, text_y);
    }
}
void menu::handle_mouse_click(sf::Vector2f mp) {
    // New Game
    if (button[0].getGlobalBounds().contains(mp)) {

        //  machine->changeState(new CharacterSelectState(machine));
    }
    // Continue
    if (button[1].getGlobalBounds().contains(mp)) {
        //  machine->changeState(new PlayState(machine));
    }
    // Leaderboard
    if (button[2].getGlobalBounds().contains(mp)) {
        // machine->changeState(new LeaderboardState(machine));
    }
    // Select Level
    if (button[3].getGlobalBounds().contains(mp)) {
        //machine->changeState(new LevelSelectState(machine));
    }
    // Exit
    if (button[4].getGlobalBounds().contains(mp)) {
        exit(0);
    }
}
void menu::render(sf::RenderWindow& window) {
    // background
    window.draw(bg_sprite);

    // draw all 6 buttons
    for (int i = 0; i < 5; i++) {
        window.draw(button[i]);
        window.draw(button_text[i]);
    }
}