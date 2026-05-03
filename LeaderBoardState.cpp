#include "LeaderboardState.h"
#include "menu.h"
#include <ctime>

LeaderboardState::LeaderboardState(stateMachine* m) : machine(m)
{
    entry_count = 0;
    font.loadFromFile("arial.ttf");

    bg_tex.loadFromFile("images/background.png");
    bg_sprite.setTexture(bg_tex);
    bg_sprite.setScale(
        700.f / bg_tex.getSize().x,
        700.f / bg_tex.getSize().y);

    panel.setSize(sf::Vector2f(660, 560));
    panel.setPosition(20, 80);
    panel.setFillColor(sf::Color(0, 0, 0, 180));

    title_text.setFont(font);
    title_text.setString("LEADERBOARD");
    title_text.setCharacterSize(36);
    title_text.setFillColor(sf::Color(255, 220, 0));
    title_text.setStyle(sf::Text::Bold);
    title_text.setPosition(220, 25);

    // column headers
    std::string header_names[5] = { "RANK", "PLAYER", "SCORE", "LEVEL", "DATE" };
    float header_x[5] = { 35, 110, 290, 430, 520 };
    for (int i = 0; i < 5; i++) {
        header[i].setFont(font);
        header[i].setString(header_names[i]);
        header[i].setCharacterSize(16);
        header[i].setFillColor(sf::Color(100, 180, 255));
        header[i].setStyle(sf::Text::Bold);
        header[i].setPosition(header_x[i], 90);
    }

    back_button.setSize(sf::Vector2f(160, 45));
    back_button.setPosition(270, 645);
    back_button.setFillColor(sf::Color(180, 80, 0));
    back_text.setFont(font);
    back_text.setString("Back to Menu");
    back_text.setCharacterSize(18);
    back_text.setFillColor(sf::Color::White);
    back_text.setStyle(sf::Text::Bold);
    back_text.setPosition(283, 655);

    load_entries();
}

void LeaderboardState::load_entries()
{
    LeaderboardEntry entries[10];
    entry_count = db.get_top_10(entries);

    // top 3 get special colors
    sf::Color colors[10];
    colors[0] = sf::Color(255, 215, 0);   // gold
    colors[1] = sf::Color(192, 192, 192); // silver
    colors[2] = sf::Color(205, 127, 50);  // bronze
    for (int i = 3; i < 10; i++)
        colors[i] = sf::Color::White;

    float col_x[5] = { 35, 110, 290, 430, 520 };
    float start_y = 120.f;
    float row_gap = 45.f;

    for (int i = 0; i < entry_count; i++)
    {
        sf::Color c = colors[i];
        float y = start_y + (i * row_gap);

        // convert timestamp to readable date using ctime
        time_t t = (time_t)entries[i].timestamp;
        char buf[26];
        ctime_s(buf, sizeof(buf), &t);
        std::string date_str = buf;
        // ctime gives "Mon Jan 01 12:00:00 2025\n"
        // just take first 10 chars "Mon Jan 01"
        if (date_str.size() > 10)
            date_str = date_str.substr(4, 6) + date_str.substr(20, 4);
        // gives "Jan 012025" - clean enough

        std::string row_data[5] = {
            "#" + std::to_string(i + 1),
            entries[i].username,
            std::to_string(entries[i].score),
            std::to_string(entries[i].level_reached),
            date_str
        };

        for (int j = 0; j < 5; j++) {
            entry_texts[i][j].setFont(font);
            entry_texts[i][j].setString(row_data[j]);
            entry_texts[i][j].setCharacterSize(17);
            entry_texts[i][j].setFillColor(c);
            entry_texts[i][j].setPosition(col_x[j], y);
        }
    }
}

void LeaderboardState::render(sf::RenderWindow& window)
{
    window.draw(bg_sprite);
    window.draw(panel);
    window.draw(title_text);

    for (int i = 0; i < 5; i++)
        window.draw(header[i]);

    // separator line under headers
    sf::RectangleShape line(sf::Vector2f(660, 2));
    line.setPosition(20, 112);
    line.setFillColor(sf::Color(100, 180, 255));
    window.draw(line);

    for (int i = 0; i < entry_count; i++)
        for (int j = 0; j < 5; j++)
            window.draw(entry_texts[i][j]);

    if (entry_count == 0) {
        sf::Text empty;
        empty.setFont(font);
        empty.setString("No scores yet! Play a game to get on the board.");
        empty.setCharacterSize(20);
        empty.setFillColor(sf::Color(200, 200, 200));
        empty.setPosition(80, 300);
        window.draw(empty);
    }

    window.draw(back_button);
    window.draw(back_text);
}

void LeaderboardState::handle_mouse_click(sf::Vector2f mp)
{
    if (back_button.getGlobalBounds().contains(mp))
        machine->changeState(new menu(machine));
}