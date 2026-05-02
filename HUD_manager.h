#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Simple HUD overlay: score, lives, gems, level, active power-up.
class HUD_manager
{
private:
    sf::Font font;
    bool     fontLoaded;

    sf::Text scoreText;
    sf::Text livesText;
    sf::Text gemsText;
    sf::Text levelText;
    sf::Text powerUpText;

    // Cached display values
    int         score;
    int         lives;
    int         gems;
    int         level;
    std::string powerUpName;
    float       powerUpTimer;
    bool        hasPowerUp;

public:
    HUD_manager();

    // Called every frame to keep displayed values current.
    // Signature matches the call in playstate.cpp:
    //   hud.update_values(score, lives, gems, level, "", 0, false, 0, 1);
    void update_values(int score, int lives, int gems, int level,
                       const std::string& powerUpName, float powerUpTimer,
                       bool hasActivePowerUp, float /*unused*/, int /*playerCount*/);

    void draw(sf::RenderWindow& window);
};
