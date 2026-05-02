#pragma once
#include<SFML/Graphics.hpp>
#include"gamestate.h"
#include"statemachinee.h"
#include"player.h"
#include"snowball.h"
#include"platform.h"
#include"Botom.h"
#include"Enemy.h"
#include"Projectile.h"
#include"artillery_rocket.h"
#include"PowerUp.h"
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
	Enemy* enemies[500];
	int Enum;
	artillery_rocket* projectile[500];  
	int projectile_count;

	PowerUp_funcs* powerups[50];
	int powerup_count;

	int lives;
	int score;

	int level;

	
	//================GEM RAIN 
	static const int MAX_GEMS = 100;
	float gemX[MAX_GEMS];
	float gemY[MAX_GEMS];
	float gemVelocity[MAX_GEMS];
	bool gemCollected[MAX_GEMS];
	int gemCount = 0;
	float cashTimer = 0.0f;
	bool isCashRain = false;
	//LOAD HUD LATER
	//
public:
	playState(stateMachine* m);
	void handleInput(inputManager& input);
	void update();
	void render(sf::RenderWindow& window);
	~playState();
	void loadLevel(int levelNum);

	void spawnPowerUp(float x, float y);
	void updatePowerUps(float delta_time);
	void checkPowerUpCollisions();
	void removePowerUp(int index);

	int getScore();


	int getLevel();
	void setLevel(int lv);

	void spawnGemRain(int amount, bool isCash);
	void updateGems(float deltaTime);
	void checkGemCollisions();
	void renderGems(sf::RenderWindow& window);
};
