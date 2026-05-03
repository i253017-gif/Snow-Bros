#include "HUD_manager.h"

// ============================================================
// HUD_manager.cpp
// Written by: Ishmal (Student B)
// Spec ref: Section 12.2 - In-Game HUD
// ============================================================

HUD_manager::HUD_manager() {

    // starting values
    score = 0;
    lives = 2;   // spec says player starts with 2 lives
    gems = 0;
    level = 1;
    powerup = "";
    powerup_timer = 0;
    show_boss_bar = false;
    boss_hp = 0;
    boss_max_hp = 1;   // avoid division by zero

    // load font
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    // --- dark background strips ---
    // top bar behind score/lives/gems/level
    top_bar.setSize(sf::Vector2f(700, 50));
    top_bar.setPosition(0, 0);
    top_bar.setFillColor(sf::Color(0, 0, 0, 180));  // semi transparent black

    // bottom bar behind power-up status
    bottom_bar.setSize(sf::Vector2f(700, 35));
    bottom_bar.setPosition(0, 665);
    bottom_bar.setFillColor(sf::Color(0, 0, 0, 180));

    // --- score text (top left) ---
    score_text.setFont(font);
    score_text.setCharacterSize(18);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(10, 5);
    score_text.setString("Score: 0");

    // --- lives (top left below score) ---
    // load heart image for lives
    heart_tex.loadFromFile("images/heart.png");
    heart_sprite.setTexture(heart_tex);
    // scale down to fit HUD bar (about 20x20 pixels)
    float heart_scale = 20.f / heart_tex.getSize().x;
    heart_sprite.setScale(heart_scale, heart_scale);

    // load gem image
    gem_tex.loadFromFile("images/gem.png");
    gem_sprite.setTexture(gem_tex);
    // scale down to fit HUD bar (about 20x20 pixels)
    float gem_scale = 40.f / gem_tex.getSize().x;
    gem_sprite.setScale(gem_scale, gem_scale);
    gem_sprite.setPosition(630, 1);

    gem_text.setFont(font);
    gem_text.setCharacterSize(18);
    gem_text.setFillColor(sf::Color(100, 255, 200));
    gem_text.setPosition(665, 10);  // right of gem icon
    gem_text.setString("0");

    // --- level indicator (top center) ---
    level_text.setFont(font);
    level_text.setCharacterSize(18);
    level_text.setFillColor(sf::Color::White);
    level_text.setStyle(sf::Text::Bold);
    level_text.setPosition(290, 10);
    level_text.setString("Level 1/10");

    // --- power-up status (bottom) ---
    powerup_text.setFont(font);
    powerup_text.setCharacterSize(15);
    powerup_text.setFillColor(sf::Color::Yellow);
    powerup_text.setPosition(10, 670);
    powerup_text.setString("");  // empty until power-up is active

    // power-up timer bar background (gray)
    powerup_bar_bg.setSize(sf::Vector2f(200, 8));
    powerup_bar_bg.setPosition(10, 690);
    powerup_bar_bg.setFillColor(sf::Color(80, 80, 80));

    // power-up timer bar (yellow, shrinks as time runs out)
    powerup_bar.setSize(sf::Vector2f(200, 8));
    powerup_bar.setPosition(10, 690);
    powerup_bar.setFillColor(sf::Color::Yellow);

    // --- boss health bar (top center, boss levels only) ---
    // label
    boss_bar_label.setFont(font);
    boss_bar_label.setCharacterSize(14);
    boss_bar_label.setFillColor(sf::Color::Red);
    boss_bar_label.setStyle(sf::Text::Bold);
    boss_bar_label.setPosition(280, 55);
    boss_bar_label.setString("BOSS");

    // gray background bar
    boss_bar_bg.setSize(sf::Vector2f(300, 18));
    boss_bar_bg.setPosition(200, 75);
    boss_bar_bg.setFillColor(sf::Color(80, 80, 80));

    // red foreground bar
    boss_bar.setSize(sf::Vector2f(300, 18));
    boss_bar.setPosition(200, 75);
    boss_bar.setFillColor(sf::Color::Red);
}

// -------------------------------------------------------
// update_values()
// called every frame with latest player and game data
// updates all internal variables so draw() shows correct info
// -------------------------------------------------------
void HUD_manager::update_values(int s, int l, int g, int lv,
    std::string pu, float pu_timer,
    bool boss_visible, int b_hp, int b_max_hp) {
    score = s;
    lives = l;
    gems = g;
    level = lv;
    powerup = pu;
    powerup_timer = pu_timer;
    show_boss_bar = boss_visible;
    boss_hp = b_hp;
    boss_max_hp = b_max_hp;

    // update score text
    score_text.setString("Score: " + std::to_string(score));

    // update gem text
    gem_text.setString(std::to_string(gems));

    // update level text
    level_text.setString("Level " + std::to_string(level) + "/10");

    // update power-up text
    if (powerup != "" && powerup_timer > 0) {
        // show power-up name and time remaining
        powerup_text.setString(powerup + " - " + std::to_string((int)powerup_timer) + "s");
    }
    else {
        powerup_text.setString("");  // no active power-up
    }

    // update boss health bar width
    if (boss_max_hp > 0) {
        float ratio = (float)boss_hp / (float)boss_max_hp;
        boss_bar.setSize(sf::Vector2f(300 * ratio, 18));
    }
}

// -------------------------------------------------------
// draw()
// draws all HUD elements on screen
// called every frame AFTER game objects are drawn
// -------------------------------------------------------
void HUD_manager::draw(sf::RenderWindow& window) {

    // draw dark background strips first
    window.draw(top_bar);
    window.draw(bottom_bar);

    // --- score (top left) ---
    window.draw(score_text);

    // --- lives (top left below score) ---
    for (int i = 0; i < lives; i++) {
        heart_sprite.setPosition(10 + (i * 25), 28);
        window.draw(heart_sprite);
    }

    // --- gems (top right) ---
    window.draw(gem_sprite);
    window.draw(gem_text);

    // --- level indicator (top center) ---
    window.draw(level_text);

    // --- power-up status (bottom) ---
    if (powerup != "" && powerup_timer > 0) {
        window.draw(powerup_text);
        window.draw(powerup_bar_bg);
        window.draw(powerup_bar);
    }

    // --- boss health bar (only on boss levels) ---
    if (show_boss_bar) {
        window.draw(boss_bar_label);
        window.draw(boss_bar_bg);
        window.draw(boss_bar);
    }
}

// --- Setters ---
void HUD_manager::set_score(int s) { score = s; score_text.setString("Score: " + std::to_string(s)); }
void HUD_manager::set_lives(int l) { lives = l; }
void HUD_manager::set_gems(int g) { gems = g;  gem_text.setString(std::to_string(g)); }
void HUD_manager::set_level(int l) { level = l; level_text.setString("Level " + std::to_string(l) + "/10"); }
void HUD_manager::set_powerup(std::string name, float timer) { powerup = name; powerup_timer = timer; }
void HUD_manager::set_boss_bar(bool visible, int hp, int max_hp) {
    show_boss_bar = visible;
    boss_hp = hp;
    boss_max_hp = max_hp;
    if (max_hp > 0) {
        float ratio = (float)hp / (float)max_hp;
        boss_bar.setSize(sf::Vector2f(300 * ratio, 18));
    }
}