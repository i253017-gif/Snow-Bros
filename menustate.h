#pragma once
#include<SFML/Graphics.hpp>
#include"gamestate.h"
#include"statemachinee.h"

//inheriting from game state

class menuState : public gameState
{
private:
	stateMachine* machine; //pointer to state machine so we can change states from menu state

public:
	menuState(stateMachine* m);
	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
};
