#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "InputManager.h"


class Gameloop
{
private:
	sf::RenderWindow window;
	StateMachine machine;
	InputManager input;
public:
	Gameloop();
	void run();
};
