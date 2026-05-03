#pragma once
#include <SFML/Graphics.hpp>
#include "inputmanager.h"
#include "statemachinee.h"

class Gameloop
{
private:
    sf::RenderWindow window;
    stateMachine machine;
    inputManager input;
public:
    Gameloop();
    void run();
};