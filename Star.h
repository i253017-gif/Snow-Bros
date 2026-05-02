#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "player.h"

// Star event: one star spawns per playthrough on a random non-boss level.
// When the player collects it, 3 random power-up choices are shown.
// Player clicks a choice; the chosen type is consumed by playState::update().
class StarEvent
{
private:
    // Star pickup
    bool  active;
    float pos_x, pos_y;
    sf::RectangleShape starShape;

    // Choice overlay
    bool        showingTypes;
    std::string options[3];
    std::string chosenType;

    // UI elements for choices
    sf::RectangleShape optionBoxes[3];
    sf::Text           optionLabels[3];
    sf::Font           font;
    bool               fontLoaded;

    // Overlay background
    sf::RectangleShape overlay;

    void generateOptions();

public:
    StarEvent();

    // Call this once when the level with the star loads
    void spawn_star(float x, float y);

    // Call every frame to detect collection; shows choice UI on collection
    void check_collection(const sf::FloatRect& playerBounds);

    void draw_star  (sf::RenderWindow& window);
    void draw_types (sf::RenderWindow& window);

    bool get_showing_types() const;

    // Called from render loop when a debounced left-click is detected
    void handle_click(const sf::Vector2f& clickPos, Player& player);

    // Returns the chosen type string and clears it (empty if nothing chosen yet)
    std::string consume_chosen_type();
};
