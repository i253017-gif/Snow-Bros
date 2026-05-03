#include "menu.h"
#include "playstate.h"
#include "LeaderboardState.h"

menu::menu(stateMachine* m, std::string logged_in_user) : machine(m)
{
    username = logged_in_user;
    db.set_active_user(username);

    font.loadFromFile("arial.ttf");

    bg_texture.loadFromFile("images/background.png");
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setScale(
        700.f / bg_texture.getSize().x,
        700.f / bg_texture.getSize().y);

    float button_x = 420;
    float button_y = 280;
    float button_width = 230;
    float button_height = 50;
    float button_gap = 70;

    for (int i = 0; i < 5; i++) {
        button[i].setSize(sf::Vector2f(button_width, button_height));
        button[i].setPosition(button_x, button_y + (i * button_gap));
        button[i].setFillColor(sf::Color(180, 80, 0));
        button_text[i].setFont(font);
        button_text[i].setString(button_name[i]);
        button_text[i].setCharacterSize(20);
        button_text[i].setFillColor(sf::Color::White);
        button_text[i].setStyle(sf::Text::Bold);
        float text_x = button_x + (button_width / 2) -
            (button_text[i].getGlobalBounds().width / 2);
        float text_y = button_y + (i * button_gap) + (button_height / 2) - 12;
        button_text[i].setPosition(text_x, text_y);
    }
}

void menu::handle_mouse_click(sf::Vector2f mp)
{
    // New Game
    if (button[0].getGlobalBounds().contains(mp)) {
        db.delete_save_data();
        machine->changeState(new playState(machine, username));
    }

    // Continue
    if (button[1].getGlobalBounds().contains(mp)) {
        if (db.has_save_data()) {
            int level, lives, gems, score;
            db.load_data(level, lives, gems, score);
            playState* game = new playState(machine, username);
            game->setLevel(level);
            machine->changeState(game);
        }
    }

    // Leaderboard
    if (button[2].getGlobalBounds().contains(mp))
        machine->changeState(new LeaderboardState(machine));

    // Select Level - leave for later
    if (button[3].getGlobalBounds().contains(mp)) {
        // machine->changeState(new LevelSelectState(machine));
    }

    // Exit
    if (button[4].getGlobalBounds().contains(mp))
        exit(0);
}

void menu::render(sf::RenderWindow& window)
{
    window.draw(bg_sprite);
    for (int i = 0; i < 5; i++) {
        window.draw(button[i]);
        window.draw(button_text[i]);
    }
}