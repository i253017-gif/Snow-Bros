#pragma once
#include<SFML/Graphics.hpp>
#include"gamestate.h"
#include"statemachinee.h"
#include"player.h"
#include"snowball.h"
#include"platform.h"
#include"Botom.h"
#include"Enemy.h"

class playState : public gameState
{
private:
	stateMachine* machine;

	//=====================
	sf::Font font;
	sf::Text text;
	Player player;
	Snowball snowball[500];
	int SBnum;
	bool wasSpacePressed;  //so only one snowball per key press
	Platform platform[50];
	int Pnum;
	Enemy* enemies[200];
	int Enum;




public:
	playState(stateMachine* m);
	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
	~playState();
	void loadLevel(int levelNum);


	//actual game logic will come here
};
