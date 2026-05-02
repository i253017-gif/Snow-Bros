#include "PowerUp_funcs.h"

// Default speed and snowball-distance values that match Player constructor
static const float DEFAULT_SPEED    = 0.5f;
static const float BOOST_SPEED      = 1.0f;
static const float DEFAULT_DISTANCE = 500.0f;
static const float BOOST_DISTANCE   = 1000.0f;

PowerUp_funcs::PowerUp_funcs(const std::string& t, float x, float y, bool star)
    : type(t), pos_x(x), pos_y(y), fromStar(star), texLoaded(false)
{
    // Set timer: timed power-ups use countdown; level-end types use -1
    if (fromStar)
    {
        timer = -1.0f;  // lasts until level end
    }
    else if (type == "speed")
    {
        timer = 15.0f;
    }
    else if (type == "balloon")
    {
        timer = 10.0f;
    }
    else
    {
        // "snowball", "distance" – last until level end
        timer = -1.0f;
    }

    // Visual: coloured square as fallback (no image required)
    visual.setSize(sf::Vector2f(20.f, 20.f));
    visual.setPosition(pos_x, pos_y);

    if (type == "speed")
        visual.setFillColor(sf::Color(255, 165, 0));   // orange
    else if (type == "snowball")
        visual.setFillColor(sf::Color(200, 200, 255)); // light blue
    else if (type == "distance")
        visual.setFillColor(sf::Color(0, 200, 100));   // green
    else if (type == "balloon")
        visual.setFillColor(sf::Color(255, 100, 200)); // pink
    else
        visual.setFillColor(sf::Color::White);

    visual.setOutlineThickness(2.f);
    visual.setOutlineColor(sf::Color::Yellow);
}

void PowerUp_funcs::apply(Player& player)
{
    if (type == "speed")
    {
        player.set_speed(BOOST_SPEED);
    }
    else if (type == "snowball")
    {
        player.set_snowball_power(true);
    }
    else if (type == "distance")
    {
        player.set_snowball_distance(BOOST_DISTANCE);
    }
    else if (type == "balloon")
    {
        player.set_balloon_mode(true);
    }
}

void PowerUp_funcs::expire(Player& player)
{
    if (type == "speed")
    {
        player.set_speed(DEFAULT_SPEED);
    }
    else if (type == "snowball")
    {
        player.set_snowball_power(false);
    }
    else if (type == "distance")
    {
        player.set_snowball_distance(DEFAULT_DISTANCE);
    }
    else if (type == "balloon")
    {
        player.set_balloon_mode(false);
    }
}

void PowerUp_funcs::update(float dt)
{
    if (timer > 0.0f)
        timer -= dt;
}

void PowerUp_funcs::draw(sf::RenderWindow& window)
{
    window.draw(visual);
}

float PowerUp_funcs::get_timer() const { return timer; }
float PowerUp_funcs::get_pos_x() const { return pos_x; }
float PowerUp_funcs::get_pos_y() const { return pos_y; }
std::string PowerUp_funcs::get_type() const { return type; }
