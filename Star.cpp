#include "Star.h"
#include <cstdlib>
#include <ctime>

// All possible power-up types
static const std::string ALL_TYPES[] = { "speed", "snowball", "distance", "balloon" };
static const int         NUM_TYPES   = 4;

// Box layout for the 3 choices (centred in 700x700 window)
static const float BOX_W  = 160.f;
static const float BOX_H  = 60.f;
static const float BOX_Y  = 300.f;
static const float BOX_X0 = 60.f;
static const float BOX_GAP= 170.f;

StarEvent::StarEvent()
    : active(false), pos_x(0.f), pos_y(0.f),
      showingTypes(false), chosenType(""), fontLoaded(false)
{
    // Star visual – yellow star shape approximated as a circle
    starShape.setSize(sf::Vector2f(30.f, 30.f));
    starShape.setFillColor(sf::Color(255, 220, 0));
    starShape.setOutlineThickness(2.f);
    starShape.setOutlineColor(sf::Color::White);

    // Overlay behind choices
    overlay.setSize(sf::Vector2f(700.f, 700.f));
    overlay.setPosition(0.f, 0.f);
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    // Try system font; silently continue if unavailable
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    fontLoaded = true;

    // Pre-configure option boxes (positions set in generateOptions)
    for (int i = 0; i < 3; i++)
    {
        optionBoxes[i].setSize(sf::Vector2f(BOX_W, BOX_H));
        optionBoxes[i].setFillColor(sf::Color(40, 40, 120));
        optionBoxes[i].setOutlineThickness(3.f);
        optionBoxes[i].setOutlineColor(sf::Color(255, 220, 0));
        optionBoxes[i].setPosition(BOX_X0 + i * BOX_GAP, BOX_Y);

        optionLabels[i].setFont(font);
        optionLabels[i].setCharacterSize(18);
        optionLabels[i].setFillColor(sf::Color::White);
    }
}

void StarEvent::spawn_star(float x, float y)
{
    active = true;
    pos_x  = x;
    pos_y  = y;
    starShape.setPosition(pos_x, pos_y);
}

void StarEvent::generateOptions()
{
    // Fisher-Yates shuffle of a small local copy, pick first 3
    std::string pool[NUM_TYPES];
    for (int i = 0; i < NUM_TYPES; i++) pool[i] = ALL_TYPES[i];

    for (int i = NUM_TYPES - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::string tmp = pool[i];
        pool[i] = pool[j];
        pool[j] = tmp;
    }

    for (int i = 0; i < 3; i++)
    {
        options[i] = pool[i];
        optionBoxes[i].setPosition(BOX_X0 + i * BOX_GAP, BOX_Y);
        optionLabels[i].setString(options[i]);
        // Centre label inside box (approximate)
        optionLabels[i].setPosition(BOX_X0 + i * BOX_GAP + 10.f, BOX_Y + 18.f);
    }
}

void StarEvent::check_collection(const sf::FloatRect& playerBounds)
{
    if (!active || showingTypes) return;

    sf::FloatRect starBounds(pos_x, pos_y, 30.f, 30.f);
    if (playerBounds.intersects(starBounds))
    {
        active       = false;
        showingTypes = true;
        chosenType   = "";
        generateOptions();
    }
}

void StarEvent::draw_star(sf::RenderWindow& window)
{
    if (!active) return;
    window.draw(starShape);
}

void StarEvent::draw_types(sf::RenderWindow& window)
{
    if (!showingTypes) return;

    // Title text (built each frame – cheap enough)
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color(255, 220, 0));
    title.setStyle(sf::Text::Bold);
    title.setString("CHOOSE A POWER-UP!");
    title.setPosition(170.f, 240.f);

    window.draw(overlay);
    window.draw(title);

    for (int i = 0; i < 3; i++)
    {
        window.draw(optionBoxes[i]);
        window.draw(optionLabels[i]);
    }
}

bool StarEvent::get_showing_types() const
{
    return showingTypes;
}

void StarEvent::handle_click(const sf::Vector2f& clickPos, Player& /*player*/)
{
    if (!showingTypes) return;

    for (int i = 0; i < 3; i++)
    {
        if (optionBoxes[i].getGlobalBounds().contains(clickPos))
        {
            chosenType   = options[i];
            showingTypes = false;
            return;
        }
    }
}

std::string StarEvent::consume_chosen_type()
{
    std::string result = chosenType;
    chosenType         = "";
    return result;
}
