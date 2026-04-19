#include"gameloop.h"
//include menu state

Gameloop::Gameloop()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "Snow Bros");
	machine.changeState(new MenuState(&stateMachine));
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
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}
