#include "HUD_manager.h"
#include <sstream>
#include <iomanip>

HUD_manager::HUD_manager()
    : fontLoaded(false), score(0), lives(0), gems(0), level(0),
      powerUpTimer(0.f), hasPowerUp(false)
{
    // Try to load a system font; fall back gracefully if not found
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    // Common setup helper
    auto setup = [&](sf::Text& t, unsigned size, float x, float y)
    {
        t.setFont(font);
        t.setCharacterSize(size);
        t.setFillColor(sf::Color::White);
        t.setOutlineColor(sf::Color::Black);
        t.setOutlineThickness(1.f);
        t.setPosition(x, y);
    };

    setup(scoreText,  18, 5.f,   5.f);
    setup(livesText,  18, 5.f,  27.f);
    setup(gemsText,   18, 5.f,  49.f);
    setup(levelText,  18, 5.f,  71.f);
    setup(powerUpText,16, 5.f,  93.f);
}

void HUD_manager::update_values(int s, int l, int g, int lv,
                                const std::string& puName, float puTimer,
                                bool hasActive, float /*unused*/, int /*playerCount*/)
{
    score       = s;
    lives       = l;
    gems        = g;
    level       = lv;
    powerUpName = puName;
    powerUpTimer= puTimer;
    hasPowerUp  = hasActive;
}

void HUD_manager::draw(sf::RenderWindow& window)
{
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
    gemsText .setString("Gems:  " + std::to_string(gems));
    levelText.setString("Level: " + std::to_string(level));

    if (hasPowerUp && !powerUpName.empty())
    {
        std::ostringstream oss;
        oss << "Power: " << powerUpName;
        if (powerUpTimer > 0.f)
            oss << " (" << std::fixed << std::setprecision(1) << powerUpTimer << "s)";
        powerUpText.setString(oss.str());
        powerUpText.setFillColor(sf::Color(255, 220, 0));
    }
    else
    {
        powerUpText.setString("");
    }

    window.draw(scoreText);
    window.draw(livesText);
    window.draw(gemsText);
    window.draw(levelText);
    window.draw(powerUpText);
}
