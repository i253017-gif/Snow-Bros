#include<SFML/Graphics.hpp>
#include"gameloop.h"
#include"menustate.h"
#include"statemachinee.h"
//include menu state

Gameloop::Gameloop() : window(sf::VideoMode(700, 700), "Snow Bros")
{
	machine.changeState(new menuState(&machine));
}

void Gameloop::run() {
    while (window.isOpen()) {

        // 🔹 1. Handle window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 🔹 2. Update input
        input.update();

        // 🔹 3. Let current state handle input + update
        machine.handleInput(input);
        machine.update();

        // 🔹 4. Draw current state
        window.clear();
        machine.render(window);
        window.display();
    }
}
