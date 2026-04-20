#pragma once
#include<SFML/Graphics.hpp>
#include"gamestate.h"
#include"statemachinee.h"

class playState : public gameState
{
private:
	stateMachine* machine;

public:
	playState(stateMachine* m);
	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);


	//actual game logic will come here
};
