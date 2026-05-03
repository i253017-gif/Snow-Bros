#include "Star.h"
#include <cstdlib>
#include<iostream>

StarEvent::StarEvent() {
    std::cout << "StarEvent constructor started\n";
    star_x = 350;
    star_y = 300;
    star_collected = false;
    star_inaffect = false;
    showing_types = false;

    // ADDED
    chosen_type = "";

    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    // load star image
    star_loaded = star_texture.loadFromFile("images/star.png");
    if (star_loaded) {
        star_sprite.setTexture(star_texture);
        float scale = 40.f / star_texture.getSize().x;
        star_sprite.setScale(scale, scale);
    }
    // dark transparent overlay behind choice panel
    overlay.setSize(sf::Vector2f(700, 700));
    overlay.setPosition(0, 0);
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    // glass panel in center
    panel.setSize(sf::Vector2f(500, 300));
    panel.setPosition(100, 200);
    panel.setFillColor(sf::Color(0, 0, 0, 180));
    // title text
    title_text.setFont(font);
    title_text.setString("Choose a Power-Up!");
    title_text.setCharacterSize(24);
    title_text.setFillColor(sf::Color(255, 220, 0));  // gold color
    title_text.setStyle(sf::Text::Bold);
    title_text.setPosition(210, 215);
    // setup 3 buttons side by side
    for (int i = 0; i < 3; i++) {
        // button box
        button[i].setSize(sf::Vector2f(130, 150));
        button[i].setPosition(120 + (i * 155), 270);
        button[i].setFillColor(sf::Color(180, 80, 0));       // dark orange
        button[i].setOutlineColor(sf::Color(255, 140, 0));   // orange outline
        button[i].setOutlineThickness(2);
        // button label
        button_labels[i].setFont(font);
        button_labels[i].setCharacterSize(13);
        button_labels[i].setFillColor(sf::Color::White);
        button_labels[i].setStyle(sf::Text::Bold);
    }
    std::cout << "StarEvent constructor finished\n";
}


// generates 3 unique random power-up choices
void StarEvent::generate_types() {
    std::string all_types[] = { "speed", "snowball", "distance", "balloon" };
    std::string all_images[] = {
        "images/speed.png",
        "images/snowpower.png",
        "images/distance.png",
        "images/balloon.png"
    };
    std::string all_labels[] = {
        "Speed Boost",
        "Snowball Power",
        "Distance Boost",
        "Balloon Mode"
    };
    // shuffle to pick 3 unique types
    int indices[] = { 0, 1, 2, 3 };
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
    // assign first 3 shuffled types to choices
    for (int i = 0; i < 3; i++) {
        types[i] = all_types[indices[i]];
        // load icon for this choice
        button_tex[i].loadFromFile(all_images[indices[i]]);
        button_icons[i].setTexture(button_tex[i]);
        float scale = 60.f / button_tex[i].getSize().x;
        button_icons[i].setScale(scale, scale);
        button_icons[i].setPosition(145 + (i * 155), 290);
        // set label
        button_labels[i].setString(all_labels[indices[i]]);
        float label_x = 120 + (i * 155) + (130 / 2) -
            (button_labels[i].getGlobalBounds().width / 2);
        button_labels[i].setPosition(label_x, 390);
    }
}

// sets star position and activates it
void StarEvent::spawn_star(float x, float y) {
    star_x = x;
    star_y = y;
    star_inaffect = true;
    star_sprite.setPosition(star_x, star_y);
}

// checks if player walked over star
void StarEvent::check_collection(sf::FloatRect player_bounds) {
    if (!star_inaffect || star_collected) {
        return;
    }

    sf::FloatRect star_bounds(star_x, star_y, 40, 40);
    if (player_bounds.intersects(star_bounds)) {
        star_collected = true;
        star_inaffect = false;
        showing_types = true;
        generate_types();  // pick 3 random power-ups to show
    }
}

// draws star on screen
void StarEvent::draw_star(sf::RenderWindow& window) {
    if (!star_inaffect) {
        return;
    }
    if (star_loaded) {
        window.draw(star_sprite);
    }
    else {
        // fallback - yellow circle
        sf::CircleShape shape(20);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(star_x, star_y);
        window.draw(shape);
    }
}

// draws choice screen when star collected
void StarEvent::draw_types(sf::RenderWindow& window) {
    if (!showing_types) return;
    window.draw(overlay);
    window.draw(panel);
    window.draw(title_text);
    for (int i = 0; i < 3; i++) {
        window.draw(button[i]);
        window.draw(button_icons[i]);
        window.draw(button_labels[i]);
    }
}

// handles mouse click on choice buttons
void StarEvent::handle_click(sf::Vector2f mouse_pos, Player& player) {
    if (!showing_types) return;
    for (int i = 0; i < 3; i++) {
        if (button[i].getGlobalBounds().contains(mouse_pos)) {
            // CHANGED: don't apply here; let playState apply/track
            chosen_type = types[i];
            showing_types = false;
            break;
        }
    }
}

// ADDED: playState reads this and applies power-up (timer=-1)
std::string StarEvent::consume_chosen_type()
{
    std::string out = chosen_type;
    chosen_type = "";
    return out;
}

// getters
bool StarEvent::get_showing_types() {
    return showing_types;
}
bool StarEvent::get_star_inaffect() {
    return star_inaffect;
}
bool StarEvent::get_star_collected() {
    return star_collected;
}