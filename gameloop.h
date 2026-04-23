#pragma once
#include <SFML/Graphics.hpp>
#include "inputmanager.h"
#include "statemachinee.h"
#include"player.h"


class Gameloop
{
private:
	sf::RenderWindow window;
	stateMachine machine;
	inputManager input;
	Player player;
public:
	Gameloop();
	void run();
};
