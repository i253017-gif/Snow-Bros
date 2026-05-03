#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// ============================================================
// HUD_manager.h
// Draws all HUD elements on screen during gameplay
// Written by: Ishmal (Student B)
// Spec ref: Section 12.2 - In-Game HUD
//
// HUD Layout:
// TOP LEFT    -> Score, Lives (heart icons)
// TOP CENTER  -> Level indicator, Boss health bar (boss levels only)
// TOP RIGHT   -> Gem count
// BOTTOM      -> Active power-up name and timer
// ============================================================

class HUD_manager {

private:
    sf::Font font;

    // --- score (top left) ---
    int      score;
    sf::Text score_text;   // displays "Score: 0"

    // --- lives (top left below score) ---
    int         lives;
    sf::Texture heart_tex;
    sf::Sprite  heart_sprite;

    // --- gems (top right) ---
    int         gems;
    sf::Text    gem_text;
    sf::Texture gem_tex;
    sf::Sprite  gem_sprite;

    // --- level indicator (top center) ---
    int      level;
    sf::Text level_text;      // displays "Level 3/10"

    // --- power-up status (bottom) ---
    std::string powerup;        // name of active power-up
    float       powerup_timer;  // seconds remaining
    sf::Text    powerup_text;   // displays "SpeedBoost - 10s"
    sf::RectangleShape powerup_bar_bg;  // background bar
    sf::RectangleShape powerup_bar;     // shrinks as timer runs out

    // --- boss health bar (top center, boss levels only) ---
    bool               show_boss_bar;  // true = visible, false = hidden
    int                boss_hp;        // current boss hp
    int                boss_max_hp;    // max boss hp
    sf::RectangleShape boss_bar_bg;    // gray background
    sf::RectangleShape boss_bar;       // red foreground, shrinks as hp drops
    sf::Text           boss_bar_label; // "BOSS"

    // --- dark background strip at top ---
    sf::RectangleShape top_bar;
    sf::RectangleShape bottom_bar;

public:
    // constructor - sets up all HUD elements
    HUD_manager();

    // updates HUD values every frame
    // called by Abiha's game loop with real player data
    void update_values(int score, int lives, int gems, int level,
        std::string powerup, float powerup_timer,
        bool show_boss_bar, int boss_hp, int boss_max_hp);

    // draws everything on screen
    void draw(sf::RenderWindow& window);

    // setters - for connecting with Abiha's player class later
    void set_score(int s);
    void set_lives(int l);
    void set_gems(int g);
    void set_level(int l);
    void set_powerup(std::string name, float timer);
    void set_boss_bar(bool visible, int hp, int max_hp);
};