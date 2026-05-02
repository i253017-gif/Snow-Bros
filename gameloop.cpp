#include<SFML/Graphics.hpp>
#include"gameloop.h"
#include"menustate.h"
#include"statemachinee.h"
#include<iostream>
#include"player.h"
//include menu state

Gameloop::Gameloop() : window(sf::VideoMode(700, 700), "Snow Bros")
{                       //so window is not declared locally but is a class member
    machine.changeState(new menuState(&machine));
}
void Gameloop::run() {
    while (window.isOpen()) {
		std::cout << "For testing! Entered gameloop run function\n";
        // 🔹 1. Handle window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 🔹 2. Update input
        input.update();


        // 3. Player
       // player.handleInput(input);
       // player.update();


        // 🔹 4. Let current state handle input + update
        machine.handleInput(input);
        machine.update();

        // 🔹 5. Draw current state
        window.clear();
        machine.render(window);
        window.display();
    }
}
