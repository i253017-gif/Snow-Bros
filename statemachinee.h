#pragma once
#include "gamestate.h"

class stateMachine
{
private:
	gameState* currentState;   //->composition
	/*A pointer that points to everything that inherits from gameState. So we dont have
	to point to individual states like pause and start etc.
	its a pointer because gamestates are created at runtime on heap*/

public:
	stateMachine();
	void changeState(gameState* newState);
	void handleInput(inputManager& input);	
	void update();
	void render(sf::RenderWindow& window);
};
