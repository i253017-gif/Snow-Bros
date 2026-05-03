#include <SFML/Graphics.hpp>
#include "gameloop.h"
#include "LoginState.h"
#include "statemachinee.h"

Gameloop::Gameloop() : window(sf::VideoMode(700, 700), "Snow Bros")
{
    machine.changeState(new LoginState(&machine));
}

void Gameloop::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(
                    sf::Mouse::getPosition(window));
                machine.handleMouseClick(mousePos);
            }

            if (event.type == sf::Event::TextEntered)
                machine.handleTextInput(event.text.unicode);
        }

        input.update();
        machine.handleInput(input);
        machine.update();

        window.clear();
        machine.render(window);
        window.display();
    }
}