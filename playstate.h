#pragma once
#include<SFML/Graphics.hpp>
#include"gamestate.h"
#include"statemachinee.h"
#include"player.h"
#include"snowball.h"

class playState : public gameState
{
private:
	stateMachine* machine;

	//=====================
	sf::Font font;
	sf::Text text;
	Player player;
	Snowball snowball[100];
	int SBnum;
	bool wasSpacePressed;  //so only one snowball per key press


public:
	playState(stateMachine* m);
	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
	~playState();


	//actual game logic will come here
};
