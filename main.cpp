#include <SFML/Graphics.hpp>
#include "statemachinee.h"
#include "inputmanager.h"
#include "RegisterState.h"

// ============================================================
// main.cpp
// Written by: Ishmal (Student B) - for testing login/register
// Replace with Abiha's Gameloop.cpp when integrating
// ============================================================

int main() {
    sf::RenderWindow window(sf::VideoMode(700, 700), "Snow Bros");
    window.setFramerateLimit(60);

    stateMachine machine;
    inputManager input;

    // start with register screen first per spec
    machine.changeState(new RegisterState(&machine));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // close window
            if (event.type == sf::Event::Closed)
                window.close();

            // text input - passes typed characters to current state
            if (event.type == sf::Event::TextEntered)
                machine.handleTextInput(event.text.unicode);

            // mouse click - passes position to current state
            if (event.type == sf::Event::MouseButtonReleased)
                machine.handleMouseClick(sf::Vector2f(
                    (float)event.mouseButton.x,
                    (float)event.mouseButton.y));
        }

        // update
        input.update();
        machine.handleInput(input);
        machine.update();

        // render
        window.clear();
        machine.render(window);
        window.display();
    }

    return 0;
}