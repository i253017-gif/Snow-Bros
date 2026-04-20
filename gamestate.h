#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
class gameState
{
public:
	virtual void handleInput(inputManager& input) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	virtual ~gameState();
};
//just a base class for states so does not need a cpp
