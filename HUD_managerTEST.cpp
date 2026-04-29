#include <SFML/Graphics.hpp>
#include "HUD_manager.h"

// ============================================================
// hud_test.cpp
// Tests HUD_manager visually
// Written by: Ishmal (Student B)
// ============================================================

int main() {
    sf::RenderWindow window(sf::VideoMode(700, 700), "HUD Test");
    window.setFramerateLimit(60);

    HUD_manager hud;

    // test values
    int   score = 1500;
    int   lives = 2;
    int   gems = 75;
    int   level = 3;
    std::string powerup = "SpeedBoost";
    float powerup_timer = 10.0f;
    bool  show_boss_bar = false;
    int   boss_hp = 15;
    int   boss_max_hp = 20;

    sf::Clock clock;  // to count time

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // press B to toggle boss bar
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::B)
                show_boss_bar = !show_boss_bar;

            // press L to go to next level
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::L)
                level = std::min(level + 1, 10);

            // press S to add score
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::S)
                score += 500;

            // press G to add gems
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::G)
                gems += 10;
        }

        // count down power-up timer
        float dt = clock.restart().asSeconds();
        if (powerup_timer > 0) {
            powerup_timer -= dt;
            if (powerup_timer <= 0) {
                powerup_timer = 0;
                powerup = "";  // power-up expired
            }
        }

        // update HUD with test values
        hud.update_values(score, lives, gems, level,
            powerup, powerup_timer,
            show_boss_bar, boss_hp, boss_max_hp);

        // draw
        window.clear(sf::Color(30, 30, 50));  // dark background for testing
        hud.draw(window);
        window.display();
    }

    return 0;
}