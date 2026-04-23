#pragma once
#include<SFML/Graphics.hpp>
#include"gamestate.h"
#include"statemachinee.h"
#include"player.h"

class playState : public gameState
{
private:
	stateMachine* machine;

	//=====================
	sf::Font font;
	sf::Text text;
	Player player;

public:
	playState(stateMachine* m);
	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
	~playState();


	//actual game logic will come here
};
