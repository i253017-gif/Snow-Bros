#pragma once
#include<SFML/Graphics.hpp>
#include"gamestate.h"
#include"statemachinee.h"
#include"player.h"
#include"snowball.h"
#include"platform.h"
#include"Botom.h"
#include"Enemy.h"
#include"PowerUp_funcs.h"
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


	/////////=======ADDED BYYYYY ISHMALLLLLLLLLLLLLL===========///
	PowerUp_funcs* powerups[50];//js yo calculate how many power ups are active on screen
	int  PUnum; //the no. of active powerups
	Score_manager  score_mgr;//used to increase points ehen power up is picked


public:
	playState(stateMachine* m);
	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
	~playState();
	void loadLevel(int levelNum);


	//actual game logic will come here
};
